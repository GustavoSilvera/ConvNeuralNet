#include "/home/gustavo/OF/libs/openFrameworks/ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    const double window_scale = 0.7;
    const int initWidth = int(2000 * window_scale);
    const int initHeight = int(1700 * window_scale);
    ofSetupOpenGL(initWidth,initHeight,OF_WINDOW);			// <-------- setup the GL context
    //glutInitDisplayString( "rgba double samples>=4 ");
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_MULTISAMPLE);
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
