#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include <vector>

class layer {
public:
  layer(size_t n = 0) : num_neurons(n) {
    init_rand();//instantiation randomizes weights
  }
  //  layer(const layer&) = delete;
  void init_rand();
  //getters
  size_t get_num_neurons() const;
  neuron get_neuron(size_t indx);
  //setters
  void set_neuron(size_t indx, double weight);
  void update_weights(std::vector<double> values);
private:
  size_t num_neurons;
  std::vector<neuron> n;
};

#endif // LAYER_H
