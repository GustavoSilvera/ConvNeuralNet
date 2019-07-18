#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

class graph {
private:
    Vec2d origin;
    std::vector<double> data;
    Vec2d dimens{500, 200};//500px wide, 200px tall
    Vec2d axis_scale{100, 100};
    void rescale();
    void resize();
public:
    graph(Vec2d o) : origin(o) {}
    void add_data(double a);
    void draw();
};

#endif // GRAPH_H
