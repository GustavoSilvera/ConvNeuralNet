#include "neuron.h"

void neuron::draw(float s)
{
    size = s;
    ofFill();
    const int bg_col = int(255*val);
    ofSetColor(bg_col, bg_col, bg_col);//gradient background circle
    ofDrawCircle(pos.x, pos.y, size);
    ofNoFill();
    ofSetColor(255, 255, 255);//white rim
    ofDrawCircle(pos.x, pos.y, size);
    drawFontText(val, pos);//only draw if non-negative (not -1 [empty])
}
