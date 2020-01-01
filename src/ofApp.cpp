#include "ofApp.h"

void ofApp::setup(){
  //seed random number generator
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  cnn.init();
  //  cnn.training = true;
}

//--------------------------------------------------------------
void ofApp::update(){
  //no use for update function because this is a terminal program, not graphical
}
