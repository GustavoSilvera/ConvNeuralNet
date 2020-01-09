#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

class graph {
public:
    graph(dvec2 o) : origin(o) {}
    graph(dvec2 o, double min) : origin(o), minimum(min) {}
    void add_data(double a);
    void set_pos(int x, int y);
    void draw();
private:
    dvec2 origin;
    std::vector<double> data;
    dvec2 dimens{500, 200};//500px wide, 200px tall
    dvec2 axis_scale{100, 100};
    void rescale();
    void resize();
    double minimum = 100;
};

#endif // GRAPH_H
