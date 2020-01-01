#include <iostream>
#include "convneuralnet.h"
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

void show_commands(){
  cout << "Inputs:\n";
  cout << "  (test)   ===> input new data and compare" << endl
       << "  (output) ===> output network data to output.txt" << endl
       << "  (cost)   ===> print average network cost" << endl
       << "  (train)  ===> begin training of neural net" << endl
       << "  (multi)  ===> use multithreading computation" << endl
       << "  (single) ===> use single-core computation" << endl
       << "  (reset)  ===> reset network and randomize all weights" << endl
       << "  (exit)   ===> exit from program(1)";
}

int main(){
  srand(stime(nullptr));
  net n_x(0, {3, 4, 2, 1}, true, 1);
  net n_y(1, {3, 2, 4, 1}, false, 1);
  net n_z(2, {3, 4, 2, 1}, true, 1);
  convneuralnet a{{n_x, n_y, n_z}};
  std::cout << "\nBuilding Convolutional Neural Net with " << a.get_num_networks() << " networks";
  std::cout << "\nStarting setup...";
  a.init();
  std::cout << "setup complete.\n";
  cout << "Welcome to Convolutional Neural Net v1.0.0\n";
  cout << "Type (Help) or (H) or (?) to see all options and input commands (Ignore parens)\n";
  show_commands();
  while(true){
    string input;
    cout << "Next Command:\n" << ">>";
    cin >> input;//wait for command
    cout << endl;
    //would like to use a switch statement but C++ wont allow for string comparisons .. :(
    if (input == "Help" || input == "H" || input == "h" || input == "?"){
      show_commands();
    }
    else if (input == "test"){
      a.new_data();
    }
    else if (input == "output"){
      a.output();
    }
    else if (input == "cost"){
      cout << "Average Cost: " << a.get_avg_cost() << endl;
    }
    else if (input == "train"){
      a.begin_train();
    }
    else if (input == "multi"){
      a.use_threads();
    }
    else if (input == "single"){
      a.use_single();
    }
    else if (input == "reset"){
      a.reset();
    }
    else if (input == "exit"){
      cout << "Exiting...\n";
      return 0;
    }
  }
  return 0;
}
