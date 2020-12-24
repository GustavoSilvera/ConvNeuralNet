#include "neuron.h"
#include "util.h"

double neuron::get_weight() const
{
  //getter for weight wariable
  return weight;
}
vec2 neuron::get_pos() const
{
  return pos;
}
void neuron::set_weight(const double value)
{
  //setter for weight variable
  weight = value;
}
void neuron::set_pos(vec2 p)
{
  pos = p;
}
void neuron::border_color(double value)
{                      //updates rim around neurons based on biases
  double scalar = 255; //bias_max, being the bias's maximum
  double color = abs(scalar * value);
  if (value > 0)
    col = (vec3{0, color, 0});
  else
    col = (vec3{color, 0, 0});
}
void neuron::draw() const
{
  ofFill();
  const int bg_col = int(clampd(0, 255, 255 * weight));
  ofSetColor(bg_col, bg_col, bg_col); //gradient background circle
  ofDrawCircle(pos.x, pos.y, size);
  ofNoFill();
  ofSetColor(int(col.x), int(col.y), int(col.z)); //white rim
  ofDrawCircle(pos.x, pos.y, size);
  if (col.z != 255)
  { //for coloured borders draw them a little bit thicker (more rims)
    ofDrawCircle(pos.x, pos.y, size + 1);
    ofDrawCircle(pos.x, pos.y, size + 2);
  }
  ofSetColor(255, 255, 255);
  drawFontText(weight, pos, 20); //only draw if non-negative (not -1 [empty])
}
