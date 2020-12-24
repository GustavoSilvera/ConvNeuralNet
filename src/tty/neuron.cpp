#include "neuron.h"

double neuron::get_weight() const
{
  //getter for weight variable
  return weight;
}

void neuron::set_weight(const double value)
{
  //setter for weight variable
  weight = value;
}
