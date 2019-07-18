#ifndef NEURON_H
#define NEURON_H
#include "util.h"

class neuron {
public:
    neuron() : val(-1) {}
    neuron(double v, Vec2d p) : val(v), pos(p) {}
    double val = 0;//weight
    Vec2d pos;
    Vec3d col{1, 1, 1};
    double size = 0;
    void draw(float s);
};

#endif // NEURON_H
