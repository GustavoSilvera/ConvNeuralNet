#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    int initWidth = 2000;
    int initHeight = 1500;
    ofSetupOpenGL(initWidth,initHeight,OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
