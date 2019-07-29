#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //seed random number generator
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    init_window_x = new_window_x = float(ofGetWidth());
    init_window_y = new_window_y = float(ofGetHeight());
    cnn.init();
    corner_fps.x = ofGetWidth() - 300;
    corner_fps.y = 0 + 160;
    renderFont();
    // clear out the window with black
    ofSetBackgroundColor(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    //n.update_layers();//always recalculating new layer neuron values
    for (int i = 0; i < 10; i++) {
        if (cnn.training) {
            cnn.avg_improve();
            g_avgcost.add_data(cnn.avg_cost);
            if(cnn.last_cost > 0) g_marginalcost.add_data(cnn.last_cost - cnn.avg_cost);//marginal (difference) cost
            if (cnn.avg_cost < 1) cnn.training = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    glPushMatrix();
    /*float scale_x = new_window_x/init_window_x;
    float scale_y = new_window_y/init_window_y;
    ofScale(scale_x, scale_y);*/
    cnn.draw();
    g_avgcost.draw();
    g_marginalcost.draw();
    ofSetColor(0, 255, 0);
    drawFontText(double(ofGetFrameRate()), vec2(corner_fps.x, corner_fps.y));
    //drawFontText(n.cost, Vec2f(corner_fps.x, corner_fps.y + 80));
    ofSetColor(255, 255, 255);
    drawFontText(cnn.avg_cost, vec2(corner_fps.x, corner_fps.y + 2 * 80));
    drawFontText(cnn.network[0].data.size(), vec2(corner_fps.x, corner_fps.y + 3 * 80));
    glPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    #define OF_KEY_SPACE 32//OF dosent have it... :/
    if (key == OF_KEY_SPACE) {//refreshed (new) model
        cnn.new_data();//only first line
    }
    if (key == OF_KEY_BACKSPACE) {//computes total average cost
        //cnn.comp_avg_cost();//computes total average cost of the entire CONVOLUTIONAL NN
        cnn.output();
        //cnn.slight_push(0.1);//slight push in random dir for all the weights/biases (to kick net out of stagnation)
    }
    if (key == OF_KEY_SHIFT) {//begins the training
        cnn.training = !cnn.training;
    }
    if (key == OF_KEY_RETURN) {//new random DATA
        cnn.randomize_weights();
    }
    if(key == 27){
        OF_EXIT_APP(0);
    }
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    new_window_x = w;
    new_window_y = h;
    corner_fps.x = w - 300;
    g_avgcost.update_pos(w - 800, h - 300);
    g_marginalcost.update_pos(w - 800, h - 50);
    //cnn.update_pos(w, h);
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
*/
