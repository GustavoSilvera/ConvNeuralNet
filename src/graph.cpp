#include "graph.h"


void graph::rescale() {
    if (data.size() > 0) {
        axis_scale.y = clampf(200, 10000, *max_element(data.begin(), data.end()));//finds highest value
        axis_scale.x = data.size();
    }
}
void graph::resize() {
    while (data.size() > 200) {
        data.erase(data.begin());//deletes first element if > 100
    }
}
void graph::add_data(float a) {
    data.push_back(a);
}
void graph::draw() {
    Vec2f v_axis_pt = Vec2f(origin.x, origin.y - dimens.y);
    Vec2f h_axis_pt = Vec2f(origin.x + dimens.x, origin.y);
    ofDrawLine(origin.x, origin.y, v_axis_pt.x, v_axis_pt.y);//vertical axis
    ofDrawLine(origin.x, origin.y, h_axis_pt.x, h_axis_pt.y);//horizontal axis
    resize();
    const int num_data = data.size();
    rescale();
    drawFontText(axis_scale.y, Vec2f(origin.x, origin.y - dimens.y));
    drawFontText(axis_scale.x, Vec2f(origin.x + dimens.x, origin.y));
    ofColor(1, 1, 0);//yeller
    const Vec2f scale = { dimens.x / axis_scale.x , dimens.y / axis_scale.y };
    ofFill();
    for (int i = 0; i < num_data; i++) {
        Vec2f centre = Vec2f(origin.x + scale.x*i, origin.y - scale.y*data[i]);
        const int size = 2;
        ofDrawCircle(centre.x, centre.y, size);
    }
    if(num_data > 1) drawFontText(data[num_data - 1], Vec2f(origin.x + scale.x * num_data, origin.y - scale.y * data[num_data - 1]));
    ofColor(1, 1, 1);
}
