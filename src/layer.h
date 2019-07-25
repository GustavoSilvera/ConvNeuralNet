#ifndef LAYER_H
#define LAYER_H

#include "util.h"
#include "neuron.h"
#include <vector>

class layer {
public:
    layer()  {}
    layer(int s, vec2 p) : num_neurons(s), pos(p) {}
    int num_neurons;
    vec2 pos;
    int neuron_size = 30;
    std::vector<neuron> n;
    double total_height;
    bool hovering = false;
    const double scale = 2.5;
    void init();
    void update_pos(vec2 p);
    void update_value(std::vector<double> values, std::vector<double> biases);
    void update_value(std::vector<double> values);
    void draw();
};

#endif // LAYER_H
