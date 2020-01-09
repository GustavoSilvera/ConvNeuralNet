#ifndef CONVNEURALNET_H
#define CONVNEURALNET_H

#include "net.h"

using namespace std;

class convneuralnet {
public:
  convneuralnet(vector<net> n) : network(n), num_networks(n.size()) {}
  convneuralnet(){
    read_data();
    vector<vector<size_t>> inner_layers {{4, 2}, {3, 4}, {4, 2}};
    vector<bool> using_sigmoid {true, false, true};
    vector<size_t> maximum_weights{1, 1, 1};
    vector<vector<size_t>> final_layers;
    vector<net> n;
    for(size_t i = 0; i < num_inputs[i]; i++){//for all inputs (should be same accross all 'i')
      vector<size_t> ind_layer{num_inputs[i]};
      for(size_t j = 0; j < inner_layers[i].size(); j++){
	ind_layer.push_back(inner_layers[i][j]);
      }
      ind_layer.push_back(1);//final (output) layer
      final_layers.push_back(ind_layer);
    }
    for(size_t i = 0; i < num_inputs[i]; i++){
      net new_n{i, final_layers[i], using_sigmoid[i], maximum_weights[i]};
      n.push_back(new_n);
    }
    num_networks = n.size();
    network.swap(n);//update local network
    init();
  }
  void init();
  //getters
  size_t get_num_networks() const;
  net get_network(size_t i) const;
  bool is_training() const;
  void use_threads();
  void use_single();
  //setters
  void begin_train();
  double get_avg_cost();
  void new_data();
  void reset();
  void output();
private:
  vector<net> network;
  vector<layer> ideals;
  vector<vector<double>> total_data;//single large dataset of all i/o
  vector<size_t> num_inputs, num_outputs;
  size_t num_networks;
  double avg_cost, last_cost;//last_cost used to compute marginal
  bool training = false;
  //void update_pos(int x, int y);
  bool read_data();
  void randomize_weights();
  void train();
  void calc_avg_cost();
  bool using_threads = true;
};

#endif // CONVNEURALNET_H
