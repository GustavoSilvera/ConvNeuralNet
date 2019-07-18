#ifndef LAYER_H
#define LAYER_H

#include "util.h"
#include "neuron.h"
#include <vector>

class layer {
public:
    layer()  {}
    layer(int s, Vec2f p) : num_neurons(s), pos(p) {}
    int num_neurons;
    Vec2f pos;
    int neuron_size = 30;
    std::vector<neuron> n;
    float total_height;
    bool hovering = false;
    const float scale = 2.5;
    void init();
    void update_pos(Vec2f p);
    void update_value(std::vector<float> values);
    void draw();
};

#endif // LAYER_H
