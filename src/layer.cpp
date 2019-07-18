#include "layer.h"

void layer::init(){
    total_height = num_neurons * neuron_size * scale;
    //const float top = (getWindowHeight() / 2) - (total_height / 2);
    for (int i = 0; i < num_neurons; i++) {//n.size() is fixed as neuron_size
        //int yPos = top + scale * i * neuron_size;
        float yPos = pos.y - total_height / 2 + scale * i * neuron_size;
        n.push_back(neuron((rand() % 100) / 100.0, Vec2f(pos.x, yPos)));//random weights for now
    }
}

void layer::update_pos(Vec2f p){
    n.clear();
    for (int i = 0; i < num_neurons; i++) {//n.size() is fixed as neuron_size
        float yPos = p.y - total_height / 2 + scale * i * neuron_size;
        n.push_back(neuron((rand() % 100) / 100.0, Vec2f(p.x, yPos)));//random weights for now
    }
}

void layer::update_value(std::vector<float> values){
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
