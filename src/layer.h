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
    std::vector<neuron> n;
    double total_height;
    bool hovering = false;
    double scale = 75;//how 'spread out' the neurons are
    void init();
    void new_pos(vec2 p);
    void update_pos(vec2 p);
    void update_value(std::vector<double> values, std::vector<double> biases);
    void update_value(std::vector<double> values);
    void draw();
};

#endif // LAYER_H
