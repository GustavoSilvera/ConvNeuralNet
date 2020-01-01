#include "ofApp.h"
#include <iostream>

void show_commands(){
  cout << "Inputs:\n";
  cout << "  (test)   ===> input new data and compare" << endl
       << "  (output) ===> output network data to output.txt" << endl
       << "  (cost)   ===> print average network cost" << endl
       << "  (train)  ===> begin training of neural net" << endl
       << "  (reset)  ===> reset network and randomize all weights" << endl
       << "  (exit)   ===> exit from program(1)";
}

int main(){
  ofApp a;
  std::cout << "\nBuilding Convolutional Neural Net with " << a.cnn.get_num_networks() << " networks";
  std::cout << "\nStarting setup...";
  a.setup();
  std::cout << "setup complete.\n";
  cout << "Welcome to Convolutional Neural Net v1.0.0\n";
  cout << "Type (Help) or (H) or (?) to see all options and input commands (Ignore parens)\n";
  show_commands();
  while(true){
    string input;
    cout << "\nNext Command:\n";
    cin >> input;//wait for command
    cout << endl;
    //would like to use a switch statement but C++ wont allow for string comparisons .. :(
    if (input == "Help" || input == "H" || input == "h" || input == "?"){
      show_commands();
    }
    else if (input == "test"){
      a.cnn.new_data();
    }
    else if (input == "output"){
      a.cnn.output();
    }
    else if (input == "cost"){
      cout << "Average Cost: " << a.cnn.get_avg_cost() << endl;
    }
    else if (input == "train"){
      a.cnn.begin_train();
    }
    else if (input == "reset"){
      a.cnn.reset();
    }
    else if (input == "exit"){
      cout << "Exiting...\n";
      return 0;
    }
  }
  return 0;
}
