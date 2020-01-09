#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  //seed random number generator
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  init_window_x = new_window_x = float(ofGetWidth());
  init_window_y = new_window_y = float(ofGetHeight());
  corner_fps.x = ofGetWidth() - 150;
  corner_fps.y = 50;
  // clear out the window with black
  ofSetBackgroundColor(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
  //n.update_layers();//always recalculating new layer neuron values
  for (int i = 0; i < 10; i++) {
    if (cnn.is_training()) {
      cnn.train();
      g_avgcost.add_data(cnn.get_avg_cost());
      if(cnn.get_last_cost() > 0) g_marginalcost.add_data(cnn.get_last_cost() - cnn.get_avg_cost());//marginal (difference) cost
      if (cnn.get_avg_cost() < 1) cnn.stop_training();
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  /*float scale_x = new_window_x/init_window_x;
    float scale_y = new_window_y/init_window_y;
    ofScale(scale_x, scale_y);*/
  cnn.draw();
  g_avgcost.draw();
  g_marginalcost.draw();
  const double FPS = double(ofGetFrameRate());
  ofSetColor(int(((60.0 - FPS)/60.0)*255), int((FPS/60.0)*255), 0);
  drawFontText(double(ofGetFrameRate()), vec2(corner_fps.x, corner_fps.y));
  //drawFontText(n.cost, Vec2f(corner_fps.x, corner_fps.y + 80));
  ofSetColor(255, 255, 255);
  drawFontText(cnn.get_avg_cost(), vec2(corner_fps.x - 100, corner_fps.y + 2 * 80));
  //drawFontText(cnn.total_data.size(), vec2(corner_fps.x - 100, corner_fps.y + 3 * 80));
}
void ofApp::read_first_line() {
  //meant to update num_inputs and num_outputs from the first line of data. 
  #define MAX_LINE 500
  char cwd[MAX_LINE];
  if(getcwd(cwd, sizeof(cwd)) != NULL){//null terminated string
    std::cout << "Current working dir: " << cwd << endl;
  }
  else{
    perror("getcwd() error");
    return;
  }
  const string file_at = strcat(cwd, "/../data/data.txt");
  ifstream file(file_at);
  if(file.is_open()){
    std::cout << "  Reading from \"" << file_at << endl;
    char line[MAX_LINE];
    file.getline(line, MAX_LINE);
    string sline = line;
    size_t end_inputs = sline.find(';');
    size_t end_outputs = sline.size();
    num_inputs = 0;
    num_outputs = 0;
    size_t i = 0;
    while(sline.find(' ', i) < end_inputs){
      size_t next_space = sline.find(' ', i);//finds next instance of " " from index i
      num_inputs++;
      i = next_space + 1;//not get inf loop finding same index
    }
    std::cout << "There are " << num_inputs << " inputs" << endl;
    i = end_inputs + 2;//refresh i with new start
    while(i < end_outputs){//space is IN FRONT of datum now... -_-
      size_t next_space = sline.find(' ', i);//finds next instance of " " from index i
      if(next_space == string::npos) next_space = end_outputs;//end of line
      num_outputs++;
      i = next_space+1;//not get inf loop finding same index
    }
    std::cout << "There are " << num_outputs << " outputs" << endl;
  }
  else{
    perror("Missing file: data.txt");
    throw std::exception();
  }
}
void ofApp::print_help() const{
  std::cout << endl << "***********Help! Inputs:************" <<endl;
  std::cout << "SPACE     ==> Input next data element" << endl
	    << "RSHIFT*   ==> Begin training" << endl
	    << "M/m       ==> Use multithreading" << endl
	    << "S/s       ==> Use singlethreading" << endl
	    << "BACKSPACE ==> Save setup in output.txt" << endl
	    << "ENTER/RET ==> Reset all networks" << endl
	    << "H/h/?     ==> Output input help" << endl
	    << "ESCAPE    ==> EXIT application"<< endl;
  std::cout << "***********Help! Inputs:************" <<endl << endl;
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
    if(cnn.is_training()) {
      std::cout << "...Stopping CNN training" <<endl;
      cnn.stop_training();
    }
    else {
      std::cout << "Starting CNN training..." << endl;
      cnn.start_training();
    }
  }
  if(key == 'm' || key == 'M') {//use multithreading
    cnn.use_threads();
  }
  if(key == 's' || key == 'S') {//use singlethreading
    cnn.use_single();
  }
  if (key == OF_KEY_RETURN) {//new random DATA
    cnn.reset();
  }
  if(key == OF_KEY_ESC){
    std::cout << "Goodbye!" << endl;
    OF_EXIT_APP(0);
  }
  if(key == 'H' || key == 'h'){
    print_help();
  }
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  new_window_x = w;
  new_window_y = h;
  cnn.resize(vec2{init_window_x, init_window_y}, vec2{w, h});//update CNN to fit in screen
  corner_fps.x = w - 150;
  g_avgcost.set_pos(w - 700, h - 300);
  g_marginalcost.set_pos(w - 700, h - 50);
  //cnn.update_pos(w, h);
}
