#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

class graph {
private:
    vec2 origin;
    std::vector<double> data;
    vec2 dimens{500, 200};//500px wide, 200px tall
    vec2 axis_scale{100, 100};
    void rescale();
    void resize();
public:
    graph(vec2 o) : origin(o) {}
    void add_data(double a);
    void draw();
};

#endif // GRAPH_H
