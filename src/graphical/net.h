#ifndef NET_H
#define NET_H

#include "layer.h"
#include "string"

class net
{
public:
  net(size_t focus_var, std::vector<size_t> network,
      bool using_sig, size_t max_weight) : focus_variable(focus_var),
                                           num_layers(network.size()),
                                           using_sigmoid(using_sig),
                                           weight_max(max_weight)
  {
    for (size_t i = 0; i < num_layers; i++)
    {
      //makes copy of network into num_neurons
      num_neurons.push_back(network[i]);
    }
  }
  void init(std::vector<vec2> &pos, std::vector<std::vector<double>> &total_data, std::vector<size_t> &num_inputs);
  string output() const;
  //getters
  size_t get_num_layers() const;
  double get_avg_cost() const;
  size_t get_data_line() const;
  const size_t get_diff() const;
  layer &get_layer(size_t i); //reference
  //training
  void start_training();
  void end_training();
  void avg_improve(layer *ideal, layer *rel_ideal, std::vector<double> &t_changes, size_t layerInd = 0);
  void test_data(layer *optimal);
  void comp_avg_cost(layer *opt);
  void randomize_weights();
  void draw(std::vector<vec2> &pos);

private:
  void update_layers();
  void extract_data(std::vector<std::vector<double>> &total_data, std::vector<size_t> &num_inputs);
  void new_data(layer *optimal);
  double compute_cost(layer *optimal);
  size_t focus_variable; //which variable is being focused on
  const size_t num_layers;
  bool using_sigmoid;
  double weight_max;
  size_t num_errors = 1;
  std::vector<size_t> num_neurons;
  std::vector<layer> layers;
  std::vector<vec2> position;
  std::vector<std::vector<vec3>> col;                    //colors of specific node groups
  const size_t diff = 300;                               //300 pixel intervals TODO
  std::vector<std::vector<std::vector<double>>> weights; //weights from ind. neurons to all neurons in next layer
  std::vector<std::vector<std::vector<double>>> weight_changes;
  std::vector<std::vector<double>> bias;         //individual neurons's biases
  std::vector<std::vector<double>> bias_changes; //individual neurons's biases
  std::vector<std::vector<double>> data;         // all the data from the txt file
  bool training = false;
  double cost = 0, total_cost = 0, avg_cost = 0;
  size_t total_data_lines, data_line = 0;
  inline double sigmoid(double x);
  inline double smooth_RelU(double x);
  struct total_changes
  {
    std::vector<std::vector<double>> weight_changes;
    std::vector<double> bias_changes;
  };
  total_changes improve(int i, layer *ideal, std::vector<double> &t_changes);
  vec3 colorGrade(double w);
  void resize(const size_t w, const size_t h);
};
#endif // NET_H
