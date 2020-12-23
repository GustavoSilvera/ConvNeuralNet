#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
  neuron(double w) : weight(w) {}
  double get_weight() const;
  void set_weight(const double value);
private:
  double weight;//weight
};

#endif // NEURON_H
