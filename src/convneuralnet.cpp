#include "convneuralnet.h"
#include <algorithm>
#include <thread>
#include <iostream>

size_t convneuralnet::get_num_networks() const {
  return num_networks;
}
net convneuralnet::get_network(size_t i) const{
  return network[i];
}
bool convneuralnet::is_training() const{
  return training;
}
double convneuralnet::get_avg_cost() const {
  return avg_cost;
}
void convneuralnet::stop_training(){
  training = false;
}
void convneuralnet::init(){
  size_t largest_num_layers = 0;//the "num_layers" of the largest neural net
  for (size_t i = 0; i < num_networks; i++) {
    if (network[i].get_num_layers() >= largest_num_layers)
      largest_num_layers = network[i].get_num_layers();
  }//simply finds the num_layers of the largest neural net
  for (size_t i = 0; i < num_networks; i++) {
    //each network corresponds to one specific output, thus one 'ideal' neuron
    ideals.push_back(layer{1});//new layer of neuron past output layer
    ideals[i].init_rand();
  }

}

const string kRootDir = "..";

bool convneuralnet::read_data(){
#define MAX_LINE 100
  std::ifstream file("../src/DATA_good.txt");//using CWD
  std::ifstream file2("../src/DATA_good.txt");//need this to find "file_length" bc the istreambuf iterator DELETES the file after reading??
  size_t file_length = size_t(std::count(std::istreambuf_iterator<char>(file2),std::istreambuf_iterator<char>(), '\n'));//gets number of '\n' in the file
  if(file.is_open()){
    size_t line_num = 0;
    while (line_num < file_length) {
      char line[MAX_LINE];//default line (less than 100 chars)
      file.getline(line, MAX_LINE);
      std::vector<double> ind_data;
      std::string sline = line;
      size_t end_inputs = sline.find(';');//has to be recomputed every time (strings are diff)
      size_t end_outputs = sline.size();
      size_t i = 0;
      num_inputs.push_back(0);//initialize num_inputs[line_num]
      num_outputs.push_back(0);//initialize num_outputs[line_num]
      while(sline.find(' ', i) < end_inputs){
	size_t next_space = sline.find(' ', i);//finds next instance of " " from index i
	string datum = sline.substr(i, next_space);
	ind_data.push_back(stod(datum));//adds all inputs to ind_data
	num_inputs[line_num]++;
	i = next_space + 1;//not get inf loop finding same index
      }
      i = end_inputs + 2;//refresh i with new start
      while(i < end_outputs){//space is IN FRONT of datum now... -_-
	size_t next_space = sline.find(' ', i);//finds next instance of " " from index i
	if(next_space == std::string::npos) next_space = end_outputs;//end of line
	string datum = sline.substr(i, next_space);
	ind_data.push_back(stod(datum));//adds all outputs to ind_data
	num_outputs[line_num]++;
	i = next_space+1;//not get inf loop finding same index
      }
      line_num++;
      total_data.push_back(ind_data);
    }
  }
  else {
    std::cout << "Unable to open file" << std::getenv("CWD");
    return false;
  }
  file.close();
  return true;
}
void convneuralnet::new_data(){
  for (size_t i = 0; i < num_networks; i++) {
    network[i].test_data(&ideals[i]);
  }
}

void convneuralnet::randomize_weights(){
  for (size_t i = 0; i < num_networks; i++) {
    network[i].randomize_weights();
  }
}

void convneuralnet::comp_avg_cost(){
  last_cost = avg_cost;
  avg_cost = 0;
  for (size_t i = 0; i < num_networks; i++) {
    network[i].comp_avg_cost(&ideals[i]);
    avg_cost += network[i].get_avg_cost();
  }
  avg_cost /= num_networks;
}

void convneuralnet::train(){
  std::vector<std::thread> threads;//amdalhs law
  for(size_t i = 0; i < num_networks; i++){
    //threads.push_back(std::thread(avg_improve_thread, &network[i], &ideals[i]));
    threads.push_back(std::thread([&, i]{//creates new thread for computing individual avg_improve
				    std::vector<double> v;
				    network[i].avg_improve(&ideals[i], &ideals[i], v);
				  }));
  }
  //for(size_t i = 0; i < num_networks; i++){
  //    threads[i].join();
  //}
  for (auto &thread:threads) {
    thread.join();
  }
  //std::thread top (network[0].avg_improve, &ideals[0], &ideals[0], v);
  /*for (size_t i = 0; i < num_networks; i++) {
    std::vector<double> v;
    network[i].avg_improve(&ideals[i], &ideals[i], v);
    }*/
  comp_avg_cost();
}
void convneuralnet::output(){
  std::ofstream output("output.txt");
  for (size_t i = 0; i < num_networks; i++) {
    output << "//Network: " << i + 1 << "\n";
    output << network[i].output();
  }
  output.flush();
}
