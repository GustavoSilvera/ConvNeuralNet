#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    const int initWidth = 2000;
    const int initHeight = 1700;
    ofSetupOpenGL(initWidth,initHeight,OF_WINDOW);			// <-------- setup the GL context
    //glutInitDisplayString( "rgba double samples>=4 ");
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_MULTISAMPLE);
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
