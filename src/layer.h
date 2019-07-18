#ifndef LAYER_H
#define LAYER_H

#include "util.h"
#include "neuron.h"
#include <vector>

class layer {
public:
    layer()  {}
    layer(int s, Vec2d p) : num_neurons(s), pos(p) {}
    int num_neurons;
    Vec2d pos;
    int neuron_size = 30;
    std::vector<neuron> n;
    double total_height;
    bool hovering = false;
    const double scale = 2.5;
    void init();
    void update_pos(Vec2d p);
    void update_value(std::vector<double> values);
    void draw();
};

#endif // LAYER_H
