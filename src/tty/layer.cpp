#include "layer.h"

void layer::init_rand()
{
  //initializses the network's layer by RANDOMLY assigning to neurons
  for (size_t i = 0; i < num_neurons; i++)
  {
    double random = (std::rand() % 1000) / 1000.0;
    n.push_back(neuron{random});
  }
}
size_t layer::get_num_neurons() const
{
  return num_neurons;
}
const neuron layer::get_neuron(size_t indx) const
{
  return n[indx];
}
void layer::set_neuron(size_t indx, double weight)
{
  n[indx].set_weight(weight);
}
void layer::update_weights(std::vector<double> values)
{
  //update weights of layer's neurons with new values
  for (size_t i = 0; i < num_neurons; i++)
  {
    n[i].set_weight(values[i]);
  }
}
