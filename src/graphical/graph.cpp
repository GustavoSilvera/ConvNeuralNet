#include "graph.h"

static double average(std::vector<double> &set)
{
    double sum = 0;
    size_t num = set.size();
    for (size_t i = 0; i < num; i++)
    {
        sum += set[i];
    }
    return (sum / num);
}
void graph::rescale()
{
    const size_t data_size = data.size();
    if (data_size > 0)
    {
        axis_scale.y = clampd(minimum, 1e10, 2 * data[data_size]); //average(data);//clampd(100, 100000, double(*max_element(data.begin(), data.end())));//finds highest value
        axis_scale.x = data_size;
    }
}
void graph::set_pos(int x, int y)
{
    origin.x = x;
    origin.y = y;
}
void graph::resize()
{
    while (data.size() > 200)
    {
        data.erase(data.begin()); //deletes first element if > 100
    }
}
void graph::add_data(double a)
{
    data.push_back(a);
}
void graph::draw()
{
    dvec2 v_axis_pt = dvec2(origin.x, origin.y - dimens.y);
    dvec2 h_axis_pt = dvec2(origin.x + dimens.x, origin.y);
    ofDrawLine(float(origin.x), float(origin.y), float(v_axis_pt.x), float(v_axis_pt.y)); //vertical axis
    ofDrawLine(float(origin.x), float(origin.y), float(h_axis_pt.x), float(h_axis_pt.y)); //horizontal axis
    resize();
    const int num_data = data.size();
    rescale();
    drawFontText(axis_scale.y, dvec2(origin.x, origin.y - dimens.y));
    drawFontText(axis_scale.x, dvec2(origin.x + dimens.x, origin.y));
    ofSetColor(255, 255, 0); //yeller
    const dvec2 scale = {dimens.x / axis_scale.x, dimens.y / axis_scale.y};
    ofFill();
    for (int i = 0; i < num_data; i++)
    {
        dvec2 centre = vec2(origin.x + scale.x * i, origin.y - scale.y * data[i]);
        const int size = 2;
        if (centre.y > origin.y - dimens.y && centre.y < origin.y)
        {
            ofDrawCircle(float(centre.x), float(centre.y), size);
        }
    }
    if (num_data > 1)
        drawFontText(data[num_data - 1], vec2(origin.x + scale.x * num_data, origin.y - scale.y * data[num_data - 1]));
    ofSetColor(255, 255, 255);
}
