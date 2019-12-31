#ifndef NET_H
#define NET_H

#include "layer.h"
#include "string"

using namespace std;

class net {
public:
  net(size_t focus_var, vector<size_t> network, bool using_sig, size_t max_weight) :
    focus_variable(focus_var),
    num_layers(network.size()),
    using_sigmoid(using_sig),
    weight_max(max_weight)
  {
    for (size_t i = 0; i < num_layers; i++) {
      //makes copy of network into num_neurons
      num_neurons.push_back(network[i]);
    }
  }
  void init(vector<vector<double>> total_data, vector<int> num_inputs);
  void update_layers();
  void extract_data(vector<vector<double>> total_data, vector<int> num_inputs);
  void avg_improve(layer* ideal, layer* rel_ideal, vector<double> t_changes, size_t layerInd = 0);
  void comp_avg_cost(layer* opt);
  void new_data(layer* optimal);
  void test_data(layer* optimal);
  void randomize_weights();
  double compute_cost(layer* optimal);
  string output() const;
  //getters
  const size_t get_num_layers() const;
  double get_avg_cost() const;
  layer get_layer(size_t i) const;
  //training
  void start_training();
  void end_training();
private:
  //CNN stuff
  size_t focus_variable;//which variable is being focused on
  bool using_sigmoid;
  double weight_max;
  const size_t num_layers;
  size_t num_errors = 1;
  vector<size_t> num_neurons;
  vector<layer> layers;
  vector<vector<vector<double>>> weights;//weights from ind. neurons to all neurons in next layer
  vector<vector<vector<double>>> weight_changes;
  vector<vector<double>> bias;//individual neurons's biases
  vector<vector<double>> bias_changes;//individual neurons's biases
  vector<vector<double>> data;// all the data from the txt file
  bool training = false;
  double cost = 0, total_cost = 0, avg_cost = 0;
  size_t total_data_lines;
  size_t data_line = 0;
  double sigmoid(double x);
  double smooth_RelU(double x);
  struct total_changes {
    vector<vector<double>> weight_changes;
    vector<double> bias_changes;
  };
  total_changes improve(int i, layer* ideal, vector<double> t_changes);
};
#endif // NET_H
