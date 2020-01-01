#include "convneuralnet.h"
#include <algorithm>
#include <thread>
#include <iostream>
#include <string.h>
#include <unistd.h> /*getcwd*/

using namespace std;

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
void convneuralnet::reset(){
  new_data();
  randomize_weights();
}
void convneuralnet::begin_train(){
  for(size_t i = 0; i < 1000; i++){
    train();
  }
}
void convneuralnet::init(){
  if(read_data()) cout << "\n Read file successfully\n";
  else cout << "\n ERROR reading file\n";
  for (size_t i = 0; i < num_networks; i++) {
    //each network corresponds to one specific output, thus one 'ideal' neuron
    ideals.emplace_back(1);//new layer of neuron past output layer
    ideals[i].init_rand();
  }
  size_t i = 0;
  //initialize networks
  for(net &n : network){
    cout << "  ..Initializing network: " << i;
    n.init(total_data, num_inputs);
    cout << "... SUCCESS!\n";
    i++;
  }
  i = 0;
  for(net &n : network){//print neurons
    cout << " Network: " << i << " is built with: \n ";
    for(size_t j = 0; j < n.get_num_layers(); j++){
      cout << " -- " << n.get_layer(j).get_num_neurons();
    }
    cout << " neurons \n";
    i++;
  }
}

bool convneuralnet::read_data(){
#define MAX_LINE 500
  char cwd[MAX_LINE];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working dir: %s\n", cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }
  const string file_at = strcat(cwd, "/data.txt"); 
  ifstream file(file_at);//using CWD
  ifstream file2(file_at);//need this to find "file_length" bc the istreambuf iterator DELETES the file after reading??
  size_t file_length = size_t(count(istreambuf_iterator<char>(file2),istreambuf_iterator<char>(), '\n'));//gets number of '\n' in the file
  if(file.is_open()){
    cout << "  Reading from \"" << cwd << "/data.txt\"\n"; 
    size_t line_num = 0;
    while (line_num < file_length) {
      char line[MAX_LINE];//default line (less than 100 chars)
      file.getline(line, MAX_LINE);
      vector<double> ind_data;
      string sline = line;
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
	if(next_space == string::npos) next_space = end_outputs;//end of line
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
    cout << "Unable to open file: " << file_at << endl;
    return false;
  }
  file.close();
  return true;
}
void convneuralnet::new_data(){
  cout << "Inputting new data:" << endl;
  for (size_t i = 0; i < num_networks; i++) {
    //data line indicates which line of data is being read
    //i indicates network and focus variable
    cout << " Network " << i << ": " << total_data[network[i].get_data_line()][i] << endl;
    network[i].test_data(&ideals[i]);
    const layer& output_layer = network[i].get_layer(network[i].get_num_layers() - 1);
    const double actual_output = output_layer.get_neuron(0).get_weight();
    const double expected_output =  ideals[i].get_neuron(i).get_weight();
    const double p_err = (actual_output - expected_output);
    cout << "   Got: " << actual_output << " instead of "
	 << expected_output << " (" << p_err << " error)" << endl;
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
  vector<thread> threads;//amdalhs law
  for(size_t i = 0; i < num_networks; i++){
    //threads.push_back(thread(avg_improve_thread, &network[i], &ideals[i]));
    threads.push_back(thread([&, i]{//creates new thread for computing individual avg_improve
			       vector<double> v;
			       network[i].avg_improve(&ideals[i], &ideals[i], v);
			     }));
  }
  //for(size_t i = 0; i < num_networks; i++){
  //    threads[i].join();
  //}
  for (auto &thread:threads) {
    thread.join();
  }
  //thread top (network[0].avg_improve, &ideals[0], &ideals[0], v);
  /*for (size_t i = 0; i < num_networks; i++) {
    vector<double> v;
    network[i].avg_improve(&ideals[i], &ideals[i], v);
    }*/
  comp_avg_cost();
}
void convneuralnet::output(){
  ofstream output("output.txt");
  for (size_t i = 0; i < num_networks; i++) {
    output << "//Network: " << i + 1 << "\n";
    output << network[i].output();
  }
  output.flush();
}
