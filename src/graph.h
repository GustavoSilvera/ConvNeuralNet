#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

class graph {
private:
    Vec2f origin;
    std::vector<float> data;
    Vec2f dimens{500, 200};//500px wide, 200px tall
    Vec2f axis_scale{100, 100};
    void rescale();
    void resize();
public:
    graph(Vec2f o) : origin(o) {}
    void add_data(float a);
    void draw();
};

#endif // GRAPH_H
