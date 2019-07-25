#include "neuron.h"


void neuron::border_color(double value){//updates rim around neurons based on biases
    double scalar = (1000);//bias_max, being the bias's maximum
    double color = abs(scalar * value);
    if(value > 0) col = (vec3{0, color, 0 });
    else col = (vec3{ color, 0, 0 });
}

void neuron::draw(float s)
{
    size = s;
    ofFill();
    const int bg_col = int(clampd(0, 255, 255*val));
    ofSetColor(bg_col, bg_col, bg_col);//gradient background circle
    ofDrawCircle(pos.x, pos.y, size);
    ofNoFill();
    ofSetColor(int(col.x), int(col.y), int(col.z));//white rim
    ofDrawCircle(pos.x, pos.y, size);
    if(col.z != 255){//for coloured borders draw them a little bit thicker (more rims)
        ofDrawCircle(pos.x, pos.y, size+1);
        ofDrawCircle(pos.x, pos.y, size+2);
    }
    ofSetColor(255, 255, 255);
    drawFontText(val, pos);//only draw if non-negative (not -1 [empty])
}
