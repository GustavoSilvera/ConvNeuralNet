#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //seed random number generator
    srand(time(NULL));
    cnn.init();
    corner_fps.x = ofGetWidth() - 200;
    corner_fps.y = 0 + 160;
    // mFont = Font("Arial", 30);//fixed custom font
    // mTextureFont = gl::TextureFont::create(mFont);
}

//--------------------------------------------------------------
void ofApp::update(){
    //n.update_layers();//always recalculating new layer neuron values
   /* for (int i = 0; i < 1; i++) {
        if (cnn.training) {
            cnn.avg_improve();
            g_avgcost.add_data(cnn.avg_cost);
            if (cnn.avg_cost < 1) cnn.training = false;
        }
    }*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    // clear out the window with black
    const ofColor BLACK{0, 0, 0};
    ofClear ( BLACK );//clear window with black
    cnn.draw();
    g_avgcost.draw();
    ofColor(0, 1, 0);
    //drawFontText(getAverageFps(), Vec2f(corner_fps.x, corner_fps.y));
    //drawFontText(n.cost, Vec2f(corner_fps.x, corner_fps.y + 80));
    //drawFontText(cnn.avg_cost, Vec2f(corner_fps.x, corner_fps.y + 2 * 80));
    //drawFontText(cnn.network[0].data.size(), Vec2f(corner_fps.x, corner_fps.y + 3 * 80));


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    /*#define OF_KEY_SPACE 32//OF dosent have it... :/
    if (key == OF_KEY_SPACE) {//refreshed (new) model
        cnn.new_data(line);//only first line
        line++;
    }
    if (key == OF_KEY_BACKSPACE) {//computes total average cost
        //cnn.comp_avg_cost();//computes total average cost of the entire CONVOLUTIONAL NN
        cnn.output();
    }
    if (key == OF_KEY_SHIFT) {//begins the training
        cnn.training = !cnn.training;
    }
    if (key == OF_KEY_RETURN) {//new random DATA
        cnn.randomize_weights();
    }*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //n.hover(event.getPos());
}
/*
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
*/
