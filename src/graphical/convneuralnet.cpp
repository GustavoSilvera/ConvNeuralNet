#include "convneuralnet.h"
#include "util.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string.h>
#include <thread>
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
double convneuralnet::get_last_cost() const {
  return last_cost;
}
void convneuralnet::reset(){
  cout << "Resetting neural net...";
  randomize_weights();
  cout << "Done!\n";
}
void convneuralnet::use_threads(){
  using_threads = true;
  cout << "Now using Multithreading\n";
}
void convneuralnet::use_single(){
  using_threads = false;
  cout << "Now using a Single Core\n";
}
void convneuralnet::begin_train(){
  training = true;
  cout << "Starting CNN training:\n...";
  auto start = std::chrono::steady_clock::now();
  const size_t num_iter = 1000;
  for(size_t i = 0; i < num_iter; i++){
    train();
    if(i % num_iter/100 == 0){//every 10th
      cout << ".";
      cout.flush();//dosent affect performance much
    }
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end-start;
  std::cout << "Took " << diff.count() << "s\n";
  cout << "Success!\n";
}
void convneuralnet::start_training(){
  training = true;
}
void convneuralnet::stop_training(){
  training = false;
}

void convneuralnet::init(){
    y_scale = ofGetHeight() / num_networks;//divides the window width to the number of neural nets
    size_t largest_num_layers = 0;//the "num_layers" of the largest neural net
    for (size_t i = 0; i < num_networks; i++) {
        if (network[i].get_num_layers() >= largest_num_layers) largest_num_layers = network[i].get_num_layers();
    }//simply finds the num_layers of the largest neural net
    for (size_t i = 0; i < num_networks; i++) {
        vec2 pos{ 100, y_scale * (i + 0.5) };//init x = 100, (i+0.5) to not start top neural net at VERY top of window
        std::vector<vec2> ind_net_pos;
        ind_net_pos.emplace_back(pos.x, y_scale * (num_networks / 2.0) );//initial position (x & y) of input layer
        for(size_t j = 0; j < network[i].get_num_layers() - 2; j++){//for all layers in network[i] (not output)
            pos.x += network[i].get_diff();//intervals of diff
            ind_net_pos.emplace_back(pos.x, y_scale*(i + 0.5));
        }
        vec2 p{//position for OUTPUT layer (1 neuron ~centered)
            pos.x += network[i].get_diff(),
            (num_networks / 2.0) * y_scale + 75  * (i - 1)//pls fix aneurism
        };//divides evenly among the ypos based off number of neurons
        ind_net_pos.push_back(p);//last position for OUTPUT neuron
        network[i].init(ind_net_pos, total_data, num_inputs);//create network[i]
        ideals.emplace_back(1, vec2{p.x + network[i].get_diff(), p.y});//new layer of neuron past output layer
        ideals[i].init_rand();
        network_pos.push_back(ind_net_pos);
    }
    init_pos = network_pos;//copies to 'init' state
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
  const string file_at = strcat(cwd, "/../data/data.txt");
  ifstream file(file_at);//using CWD
  ifstream file2(file_at);//need this to find "file_length" bc the istreambuf iterator DELETES the file after reading??
  size_t file_length = size_t(count(istreambuf_iterator<char>(file2),istreambuf_iterator<char>(), '\n'));//gets number of '\n' in the file
  if(file.is_open()){
    cout << "  Reading from \"" << file_at << endl;
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
    cout << "ERROR!\nUnable to open file: " << file_at << endl;
    perror("Missing file: data.txt\n");
    throw std::exception();
    return false;
  }
  file.close();
  return true;
}
void convneuralnet::new_data(){
  cout << "Inputting new data:" << endl;
  cout << "Testing on line " << network[0].get_data_line() << " out of " << total_data.size() << endl;
  for (size_t i = 0; i < num_networks; i++) {
    //data line indicates which line of data is being read
    //i indicates network and focus variable
    cout << " Network " << i << ": " << total_data[network[i].get_data_line()][i] << endl;
    network[i].test_data(&ideals[i]);
    const layer& output_layer = network[i].get_layer(network[i].get_num_layers() - 1);
    const double actual_output = output_layer.get_neuron(0).get_weight();
    const double expected_output =  ideals[i].get_neuron(0).get_weight();
    const double p_err = (actual_output - expected_output);
    if(expected_output != 0){
      const double r_err = p_err / expected_output;//relative error
      cout << "   Got: " << actual_output << " instead of "
     << expected_output << " (" << p_err << " error, " << 100*r_err << "%)\n";
    }
    else{
      cout << "   Got: " << actual_output << " instead of "
     << expected_output << " (" << p_err << " error)\n";//NO %ERR
    }
  }
}

void convneuralnet::randomize_weights(){
  for (size_t i = 0; i < num_networks; i++) {
    network[i].randomize_weights();
  }
}

void convneuralnet::calc_avg_cost(){
  last_cost = avg_cost;
  avg_cost = 0;
  for (size_t i = 0; i < num_networks; i++) {
    network[i].comp_avg_cost(&ideals[i]);
    avg_cost += network[i].get_avg_cost();
  }
  avg_cost /= num_networks;
}

void convneuralnet::train(){
  if(using_threads){
    vector<thread> threads;//amdalhs law
    for(size_t i = 0; i < num_networks; i++){
      //creates new thread for computing individual avg_improve
      threads.push_back(
      thread([&, i]{vector<double> v; network[i].avg_improve(&ideals[i], &ideals[i], v);})
      );
    }
    for (auto &thread:threads) {
      thread.join();
    }
  }
  //thread top (network[0].avg_improve, &ideals[0], &ideals[0], v);
  else{
    for (size_t i = 0; i < num_networks; i++) {
      vector<double> v;
      network[i].avg_improve(&ideals[i], &ideals[i], v);
    }
  }
  calc_avg_cost();
}
void convneuralnet::output(){
  #define MAX_LINE 500
    char cwd[MAX_LINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n", cwd);
    } else {
      perror("getcwd() error");
      return;
    }
    const string file_at = strcat(cwd, "/output.txt");
    cout << "Saving current Network to \"" <<file_at << "\"\n  ";
    ofstream output(file_at);
    for (size_t i = 0; i < num_networks; i++) {
      cout << "...N" << i;
      output << "//Network: " << i + 1 << "\n";
      output << network[i].output();
      cout << "...";
    }
    output.flush();
    cout << "Success!\n";
}
void convneuralnet::resize(vec2 init, vec2 current){//compares current window to initial
    for(size_t i = 0; i < num_networks; i++){
        for(size_t j = 0; j < network[i].get_num_layers(); j++){
            network_pos[i][j].x = init_pos[i][j].x * (current.x/init.x);//scales original x down by window factor
            network_pos[i][j].y = init_pos[i][j].y * (current.y/init.y);//scales original y down by window factor
            network[i].get_layer(j).set_scale(75 * double(current.y/init.y));
        }
        vec2 ideal_pos(network_pos[i][network[i].get_num_layers() - 1].x + network[i].get_diff(), network_pos[i][network[i].get_num_layers() - 1].y);
        ideals[i].set_pos(ideal_pos);//based off last value of position matrix
    }
}
void convneuralnet::draw()
{
    for (size_t i = 0; i < num_networks; i++) {
        network[i].draw(network_pos[i]);
        ideals[i].draw();//based off last value of position matrix
        //drawFontText(network[i].cost, vec2(ideals[i].pos.x + 200, ideals[i].pos.y - 30));
        drawFontText(network[i].get_avg_cost(), vec2(ideals[i].get_pos().x + 400, ideals[i].get_pos().y - 30));
    }
}
