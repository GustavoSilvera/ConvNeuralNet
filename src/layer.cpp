#include "layer.h"

void layer::init(){
    total_height = num_neurons * neuron_size * scale;
    //const double top = (getWindowHeight() / 2) - (total_height / 2);
    for (int i = 0; i < num_neurons; i++) {//n.size() is fixed as neuron_size
        //int yPos = top + scale * i * neuron_size;
        double yPos = pos.y - total_height / 2 + scale * i * neuron_size;
        n.push_back(neuron((rand() % 100) / 100.0, Vec2d(pos.x, yPos)));//random weights for now
    }
}

void layer::update_pos(Vec2d p){
    n.clear();
    for (int i = 0; i < num_neurons; i++) {//n.size() is fixed as neuron_size
        double yPos = p.y - total_height / 2 + scale * i * neuron_size;
        n.push_back(neuron((rand() % 100) / 100.0, Vec2d(p.x, yPos)));//random weights for now
    }
}

void layer::update_value(std::vector<double> values){
    for (int i = 0; i < num_neurons; i++) {
        n[i].val = values[i];//random weights for now
    }
}

void layer::draw()
{
    for (int i = 0; i < num_neurons; i++) {
        n[i].draw(neuron_size);
    }
}
