#include "ofApp.h"
#include <iostream>

int main(){
  ofApp a;
  std::cout << "\nBuilding Convolutional Neural Net with " << a.cnn.num_networks << " networks";
  for(size_t i = 0; i < a.cnn.num_networks; i++){
    std::cout << "\nNet: " << i << " = ";
    for(size_t j = 0; j < a.cnn.networks[i].num_layers; j++){
      std::cout << a.cnn.networks[j].layers[j].num_neurons; << " ";
    }
  }
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
