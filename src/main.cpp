#include "ofApp.h"
#include <iostream>

int main(){
  ofApp a;
  std::cout << "\nBuilding Convolutional Neural Net with " << a.cnn.get_num_networks() << " networks";
  for(size_t i = 0; i < a.cnn.get_num_networks(); i++){
    std::cout << "\nNet: " << i << " = ";
    for(size_t j = 0; j < a.cnn.get_network(i).get_num_layers(); j++){
      std::cout << a.cnn.get_network(j).get_layer(j).get_num_neurons() << " ";
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
