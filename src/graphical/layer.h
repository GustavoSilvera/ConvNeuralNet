#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include <vector>

class layer
{
public:
  layer(size_t s, vec2 p) : num_neurons(s), pos(p) {}
  bool hovering = false;
  void init_rand();
  //getters
  size_t get_num_neurons() const;
  const neuron get_neuron(size_t indx) const;
  vec2 get_pos() const;
  //setters
  void set_neuron(size_t indx, double weight);
  void update_weights(std::vector<double> &values, std::vector<double> &biases);
  void set_weights(std::vector<double> &values);
  void set_pos(vec2 &p);
  void set_scale(double s);
  //other
  void draw();

private:
  size_t num_neurons;
  vec2 pos;
  double scale = 75; //how 'spread out' the neurons are
  //need this?? double total_height;
  std::vector<neuron> n;
};

#endif // LAYER_H
