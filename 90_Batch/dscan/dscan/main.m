#import <Foundation/Foundation.h>
#import <ScriptingBridge/ScriptingBridge.h>
#import "Finder.h"
#define POLLING_INTERVAL 1
#define FILTER_SUFFIX ".aif"

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
            "starting up... this version of dscan(DesktopScanner) doesn't have network function.\n");
	
	// get desktop items' path
	NSMutableArray* paths = getUnixPaths();
	
	// Dump!!!
	// gets finder items and their position for first time.
	NSArray* items = getFinderItemsViaSB(paths);
	scanForDump(items);
	
	//
	// main loop
	//
	while (TRUE) {
		
		// Differences!!!
		// Scripting Bridge
		
		items = getFinderItemsViaSB(paths);
		scanForUpdates(items);
		
		sleep(POLLING_INTERVAL);
	}
	
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
	NSString* theSuffix = @FILTER_SUFFIX;
	NSMutableArray* outPaths = [[NSMutableArray alloc] init];
	NSFileManager*  fileManager = [NSFileManager defaultManager];
	
	for (NSString *aPath in [fileManager contentsOfDirectoryAtPath: theDirectory error: &error]){
		NSDictionary *attrs = [fileManager attributesOfItemAtPath: aPath error: &error];
        if( [NSFileTypeRegular compare:[attrs objectForKey: NSFileType] ]
           && [aPath hasSuffix: theSuffix]){ [outPaths addObject: aPath]; }
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
// Finder Desktop上に存在しているすべてのaiffファイルの情報を標準出力に出力します
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
// Finder Desktopで座標に変更のあったaiffファイルの情報を標準出力に出力します
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