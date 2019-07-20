#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
    neuron() : val(-1) {}
    neuron(double v, vec2 p) : val(v), pos(p) {}
    double val = 0;//weight
    vec2 pos;
    vec3 col{1, 1, 1};
    float size = 0;
    void draw(float s);
};

#endif // NEURON_H
