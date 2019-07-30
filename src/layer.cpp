#include "layer.h"

void layer::init(){
    total_height = num_neurons * scale;
    //const double top = (getWindowHeight() / 2) - (total_height / 2);
    for (int i = 0; i < num_neurons; i++) {//n.size() is fixed as neuron_size
        //int yPos = top + scale * i * neuron_size;
        double yPos = pos.y - total_height / 2 + scale * i;
        n.push_back(neuron((rand() % 100) / 100.0, vec2(pos.x, yPos)));//random weights for now
    }
}
void layer::update_pos(vec2 p){
    total_height = num_neurons * scale;
    pos = p;
}
void layer::update_value(std::vector<double> values, std::vector<double> biases){
    for (int i = 0; i < num_neurons; i++) {
        n[i].val = values[i];//random weights for now
        n[i].border_color(biases[i]);
    }
}
void layer::update_value(std::vector<double> values){
    for (int i = 0; i < num_neurons; i++) {
        n[i].val = values[i];//random weights for now
    }
}
void layer::draw(){
    for (int i = 0; i < num_neurons; i++) {
        double y_pos = double(pos.y) - total_height / 2 + scale * i ;
        n[i].update_pos(vec2{pos.x, y_pos});
        n[i].draw();
    }
}
