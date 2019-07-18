#include "graph.h"


void graph::rescale() {
    if (data.size() > 0) {
        axis_scale.y = clampd(200, 100000, double(*max_element(data.begin(), data.end())));//finds highest value
        axis_scale.x = data.size();
    }
}
void graph::resize() {
    while (data.size() > 200) {
        data.erase(data.begin());//deletes first element if > 100
    }
}
void graph::add_data(double a) {
    data.push_back(a);
}
void graph::draw() {
    Vec2d v_axis_pt = Vec2d(origin.x, origin.y - dimens.y);
    Vec2d h_axis_pt = Vec2d(origin.x + dimens.x, origin.y);
    ofDrawLine(float(origin.x), float(origin.y), float(v_axis_pt.x), float(v_axis_pt.y));//vertical axis
    ofDrawLine(float(origin.x), float(origin.y), float(h_axis_pt.x), float(h_axis_pt.y));//horizontal axis
    resize();
    const int num_data = data.size();
    rescale();
    drawFontText(axis_scale.y, Vec2d(origin.x, origin.y - dimens.y));
    drawFontText(axis_scale.x, Vec2d(origin.x + dimens.x, origin.y));
    ofSetColor(255, 255, 0);//yeller
    const Vec2d scale = { dimens.x / axis_scale.x , dimens.y / axis_scale.y };
    ofFill();
    for (int i = 0; i < num_data; i++) {
        Vec2d centre = Vec2d(origin.x + scale.x*i, origin.y - scale.y*data[i]);
        const int size = 2;
        ofDrawCircle(float(centre.x), float(centre.y), size);
    }
    if(num_data > 1) drawFontText(data[num_data - 1], Vec2d(origin.x + scale.x * num_data, origin.y - scale.y * data[num_data - 1]));
    ofSetColor(255, 255, 255);
}
