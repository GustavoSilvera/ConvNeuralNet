#include "ofApp.h"
#include <iostream>

int main(){
  ofApp a;
  std::cout << "\nBuilding Convolutional Neural Net with " << a.cnn.get_num_networks() << " networks";
  std::cout << "\nStarting setup...";
  a.setup();
  std::cout << "setup complete.\n";
  std::cout << "\nReading data from: ";// << std::getenv("CWD");
  std::cout << "read this?";
  while(true){
    a.update();
  }
  return 0;
}
