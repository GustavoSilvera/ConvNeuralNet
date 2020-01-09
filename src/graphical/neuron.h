#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
  //negative constructor
  neuron(double v, vec2 p) : weight(v), pos(p) {}
  //getters
  double get_weight() const;
  vec2 get_pos() const;
  //setters
  void set_weight(const double value);
  void set_pos(vec2 p);
  //other
  void draw() const;
  void border_color(double value);
private:
  vec3 col{255, 255, 255};//white
  double size = 30;
  double weight;
  vec2 pos;
};

#endif // NEURON_H
