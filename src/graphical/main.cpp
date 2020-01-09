#include "/home/gustavo/OF/libs/openFrameworks/ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    const double window_scale = 0.7;
    const size_t initWidth = size_t(2000 * window_scale);
    const size_t initHeight = size_t(1700 * window_scale);
    ofSetupOpenGL(initWidth,initHeight,OF_WINDOW);			// <-------- setup the GL context
    //glutInitDisplayString( "rgba double samples>=4 ");
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_MULTISAMPLE);
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
