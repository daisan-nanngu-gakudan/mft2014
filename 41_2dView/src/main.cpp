#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofApp * app = new ofApp();  
	app->setup();  
	while(1){
		app->update();
		sleep(0.5);
	}  
}
