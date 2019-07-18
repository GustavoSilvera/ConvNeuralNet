#include "neuron.h"

void neuron::draw(float s)
{
    size = s;
    ofColor(val, val, val);//gradient background circle
    ofFill();
    ofDrawCircle(pos.x, pos.y, size);
    ofColor(col.x, col.y, col.z);//fully colored inner circle
    ofNoFill();
    ofDrawCircle(pos.x, pos.y, size);
    ofColor(1, 1, 1);//back to white
    //drawFontText(val, pos);//only draw if non-negative (not -1 [empty])
}
