#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
    neuron() : val(-1) {}
    neuron(double v, vec2 p) : val(v), pos(p) {}
    double val = 0;//weight
    vec2 pos;
    vec3 col{255, 255, 255};
    float size = 30;
    void border_color(double value);
    void update_pos(vec2 p);
    void draw();
};

#endif // NEURON_H
