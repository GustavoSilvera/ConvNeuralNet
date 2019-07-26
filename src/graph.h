#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

class graph {
private:
    dvec2 origin;
    std::vector<double> data;
    dvec2 dimens{500, 200};//500px wide, 200px tall
    dvec2 axis_scale{100, 100};
    void rescale();
    void resize();
    double minimum = 100;
public:
    graph(dvec2 o) : origin(o) {}
    graph(dvec2 o, double min) : origin(o), minimum(min) {}
    void add_data(double a);
    void update_pos(int x, int y);
    void draw();
};

#endif // GRAPH_H
