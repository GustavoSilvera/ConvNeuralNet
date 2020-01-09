#include "layer.h"

void layer::init_rand(){
  const double total_height = num_neurons * scale;
  //initializses the network's layer by RANDOMLY assigning to neurons
  for (size_t i = 0; i < num_neurons; i++) {
    double random = (rand() % 1000) / 1000.0;
    const double yPos = pos.y - total_height / 2 + scale * i;
    n.push_back(neuron{random, vec2(pos.x, yPos)});
  }
}
size_t layer::get_num_neurons() const {
  return num_neurons;
}
vec2 layer::get_pos() const{
  return pos;
}
const neuron layer::get_neuron(size_t indx) const{
  return n[indx];
}
void layer::set_neuron(size_t indx, double weight){
  n[indx].set_weight(weight);
}
void layer::set_scale(double s){
  scale = s;
}
void layer::set_pos(vec2 &p){
    pos = p;
}
void layer::set_weights(std::vector<double> &values){//default parameter
  //update weights of layer's neurons with new values
  for (size_t i = 0; i < num_neurons; i++) {
    n[i].set_weight(values[i]);
  }
}
void layer::update_weights(std::vector<double> &values, std::vector<double> &biases){//default parameter
  //update weights of layer's neurons with new values
  const size_t bias_size = biases.size();
  for (size_t i = 0; i < num_neurons; i++) {
    n[i].set_weight(values[i]);
    if(i < bias_size) n[i].border_color(biases[i]);//safety check
  }
}
void layer::draw(){
    const double total_height = num_neurons * scale;
    for (size_t i = 0; i < num_neurons; i++) {
        const double y_pos = double(pos.y) - total_height / 2 + scale * i ;
        n[i].set_pos(vec2{pos.x, y_pos});
        n[i].draw();
    }
}
