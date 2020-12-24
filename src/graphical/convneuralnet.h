#ifndef CONVNEURALNET_H
#define CONVNEURALNET_H

#include "net.h"

class convneuralnet
{
public:
  convneuralnet(std::vector<net> &n) : network(n), num_networks(n.size())
  {
    read_data();
    init();
  }
  convneuralnet() {} //basic version w/ nothing yet
  void init();
  void set_nets(std::vector<net> n); //NOT a reference
  //getters
  size_t get_num_networks() const;
  net get_network(size_t i) const;
  double get_avg_cost() const;
  double get_last_cost() const;
  bool is_training() const;
  void use_threads();
  void use_single();
  //setters
  void begin_train();
  void start_training();
  void stop_training();
  void new_data();
  void reset();
  void train();
  void output();
  void resize(vec2 init, vec2 current);
  void draw();

private:
  std::vector<net> network;
  std::vector<layer> ideals;
  std::vector<std::vector<double>> total_data; //single large dataset of all i/o
  std::vector<std::vector<vec2>> network_pos, init_pos;
  std::vector<size_t> num_inputs, num_outputs;
  size_t num_networks;
  double avg_cost, last_cost; //last_cost used to compute marginal
  bool training = false;
  //void update_pos(int x, int y);
  bool read_data();
  void randomize_weights();
  void calc_avg_cost();
  bool using_threads = true;
  double y_scale;
};

#endif // CONVNEURALNET_H
