#include <iostream>
#include "convneuralnet.h"
#include <vector>
#include <thread>
#include <fstream>
#include <string.h>
#include <unistd.h> /*getcwd*/

using namespace std;

void show_commands(){
  cout << "Inputs:\n";
  cout << "  (test)   ===> input new data and compare" << endl
       << "  (save)   ===> save current network data to output.txt" << endl
       << "  (cost)   ===> print average network cost" << endl
       << "  (train)  ===> begin training of neural net" << endl
       << "  (multi)  ===> use multithreading computation" << endl
       << "  (single) ===> use single-core computation" << endl
       << "  (reset)  ===> reset network and randomize all weights" << endl
       << "  (exit)   ===> exit from program(1)";
}
void read_first_line(size_t &num_inputs, size_t &num_outputs) {
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
int main(){
  srand(time(nullptr));
  std::vector<net> nets;
  size_t num_inputs = 0;
  size_t num_outputs = 0;
  read_first_line(num_inputs, num_outputs);//initialized num_inputs/outputs
    if(num_inputs == 0 || num_outputs == 0) throw std::exception();
    std::vector<std::vector<size_t>> num_layer_neurons;
    for(size_t i = 0; i < num_inputs; i++){//for each network
      //randomly generate internal layers
      std::vector<size_t> num_neurons;
      const size_t num_layers = randint(1,3);//min of 1 layer, max of 3
      for(size_t j = 0; j < num_layers; j++){
	num_neurons.push_back(randint(1, 5));//each layer can have 0-5 neurons
      }
      num_layer_neurons.push_back(num_neurons);
    }
    for(size_t i = 0; i < num_inputs; i++){
      std::vector<size_t> layer_neurons = {num_inputs};//initialized w/ num inputs
      const size_t num_layers = num_layer_neurons[i].size();
      for(size_t j = 0; j < num_layers; j++){
	layer_neurons.push_back(num_layer_neurons[i][j]);//internal layer data
      }
      layer_neurons.push_back(1);//each net focuses on a single output
      bool using_sig = true;
      if(randint(0,1) == 1) using_sig = false;
      nets.emplace_back(i, layer_neurons,  using_sig, randint(1,2));//add to vector of nets
    }
    //random network
    convneuralnet cnn{nets};
  std::cout << "\nBuilding Convolutional Neural Net with " << cnn.get_num_networks() << " networks";
  std::cout << "\nStarting setup...";
  cnn.init();
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
      cnn.new_data();
    }
    else if (input == "save"){
      cnn.output();
    }
    else if (input == "cost"){
      cout << "Average Cost: " << cnn.get_avg_cost() << endl;
    }
    else if (input == "train"){
      cnn.begin_train();
    }
    else if (input == "multi"){
      cnn.use_threads();
    }
    else if (input == "single"){
      cnn.use_single();
    }
    else if (input == "reset"){
      cnn.reset();
    }
    else if (input == "exit"){
      cout << "Exiting...\n";
      return 0;
    }
    else{
      cout << "Exiting...\n";
      return 0;
    }
  }
  return 0;
}
