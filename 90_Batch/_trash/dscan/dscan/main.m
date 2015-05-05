#import <Foundation/Foundation.h>
#import <ScriptingBridge/ScriptingBridge.h>
#import "Finder.h"
#define POLLING_INTERVAL 1
#define FILTER_SUFFIX1 ".aif"
#define FILTER_SUFFIX2 ".aiff"
#define FILTER_SUFFIX3 ".wav"
#define FILTER_SUFFIX4 ".mov"
#define FILTER_SUFFIX5 ".txt"

// prototypes
NSMutableArray* getUnixPaths();
NSArray* getFinderItemsViaSB(NSMutableArray*);
void scanForDump(NSArray*);
void scanForUpdates(NSArray*);

void setSigHandler();
void exitWithCleaning();

// variables
NSAutoreleasePool* pool;
NSMutableDictionary* dict;

//
// - New Project: C -> Foundation でプロジェクトを作成する
// - Finder.h: "sdef /System/Library/CoreServices/Finder.app| sdp -fh --basename Finder"
// - OS X 10.9 + Xcode 5.1では, AutoCountingMode: off とすること
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// - . . . . . . . . m a i n  . . . . . . . .
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main (int argc, const char * argv[]) {
	
	// stdout のバッファリングを解除
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
	
	// シグナルハンドラ設定
	setSigHandler(SIGINT);
	
	pool = [[NSAutoreleasePool alloc] init];
	dict = [NSMutableDictionary dictionary];
	   
	fprintf(stderr,
            "[INFO]dscan(batch)\n"
            "[INFO]...filters aif/aiff/wav/mov/txt\n"
            "[INFO]starting up... this version of dscan(DesktopScanner) doesn't have network function.\n");
	
	// get desktop items' path
	NSMutableArray* paths = getUnixPaths();
	
	// Dump!!!
	// gets finder items and their position for first time.
	NSArray* items = getFinderItemsViaSB(paths);
	scanForDump(items);
		
	[items dealloc];
	[pool drain];
	
	return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// - .... Other Funcitons ....
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//
// getUnixPath()
//	~/Desktopにある"aif"ファイルのUnixパスを、NSMutableArrayにセットして返却します。
//
NSMutableArray* getUnixPaths(){
	
	NSArray*  paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);
	NSString* theDirectory = [paths objectAtIndex:0];
	NSError*  error;
	
	// filter with certain extentions
	NSString* theSuffix1 = @FILTER_SUFFIX1;
    NSString* theSuffix2 = @FILTER_SUFFIX2;
    NSString* theSuffix3 = @FILTER_SUFFIX3;
    NSString* theSuffix4 = @FILTER_SUFFIX4;
    NSString* theSuffix5 = @FILTER_SUFFIX5;
    
	NSMutableArray* outPaths = [[NSMutableArray alloc] init];
	NSFileManager*  fileManager = [NSFileManager defaultManager];
	
	for (NSString *aPath in [fileManager contentsOfDirectoryAtPath: theDirectory error: &error]){
		NSDictionary *attrs = [fileManager attributesOfItemAtPath: aPath error: &error];
        if( [NSFileTypeRegular compare:[attrs objectForKey: NSFileType] ]
           && ([aPath hasSuffix: theSuffix1]
                || [aPath hasSuffix: theSuffix2]
                || [aPath hasSuffix: theSuffix3]
                || [aPath hasSuffix: theSuffix4]
                || [aPath hasSuffix: theSuffix5]
               ))
        { [outPaths addObject: aPath]; }
	}
	return outPaths;
}

//
// getFinderItemsViaSB()
// パスの集合を引数に指定して、FinderItemオブジェクトの集合を取得します
//
NSArray* getFinderItemsViaSB(NSMutableArray* unixPaths){
	
	// いったん全部取得する
	FinderApplication *finder = [SBApplication applicationWithBundleIdentifier: @"com.apple.finder"];
	SBElementArray *fitems = [[finder desktop] files];	// SBで全部取る
	
	// aiffファイルだけ選別して詰め直す
	NSArray *filteredItems = [[NSMutableArray alloc] init];
	for (id path in unixPaths) { [filteredItems addObject: [fitems objectWithName: path]];}
	
	return filteredItems;
}

//
// Finder Desktop上に存在しているすべての抽出対象ファイルの情報を標準出力に出力します
//
void scanForDump(NSArray* items){
	
	NSUInteger index = 0;
	
	for (id aItem in items){
		
		// get current positions
		index++;
		CGPoint p = NSPointToCGPoint([aItem desktopPosition]);
		NSValue *pAsObj = [NSValue value:&p withObjCType: @encode(CGPoint)];
		[dict setValue:pAsObj forKey:[aItem name]];
		
		// output in stdout
		char* filename = (char*) [[aItem name] UTF8String];
		fprintf(stdout, "/dump %d %s %d %d\n", index, filename, (int)p.x, (int)p.y);
		
	}
}

//
// Finder Desktopで座標に変更のあった抽出対象ファイルの情報を標準出力に出力します
//
void scanForUpdates(NSArray* items){
	
	NSUInteger index = 0;
	
	for (id aItem in items){
		
		// get current positions
		index++;
		CGPoint p = NSPointToCGPoint([aItem desktopPosition]);
		NSValue *pAsObj = [NSValue value:&p withObjCType: @encode(CGPoint)];
		
		// lookup dictionary which contains previous position
		NSValue *prevPointAsNSValue = [dict valueForKey: [aItem name]];
		if ([ pAsObj isEqualTo: prevPointAsNSValue]){ continue; }
        
		CGPoint prevP;
		[prevPointAsNSValue getValue: &prevP];
        
		[dict setValue: pAsObj forKey: [aItem name]];
        
		// output in stdout
		char* filename = (char*) [[aItem name] UTF8String];
		fprintf(stdout, "/update %d %s %d %d\n", index, filename, (int)p.x, (int)p.y );
		
	}
}

void setSigHandler(int signame){
	if (signal(signame, exitWithCleaning) == SIG_ERR) exit(1);
}

void exitWithCleaning(){
	printf("exit with cleaning\n");
	[pool drain];
	abort();
}