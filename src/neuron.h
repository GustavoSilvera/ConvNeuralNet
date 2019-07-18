#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
    neuron() : val(-1) {}
    neuron(float v, Vec2f p) : val(v), pos(p) {}
    float val = 0;//weight
    Vec2f pos;
    Vec3f col{1, 1, 1};
    float size = 0;
    void draw(float s);
};

#endif // NEURON_H
