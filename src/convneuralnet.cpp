#include "convneuralnet.h"



void convneuralnet::init(){
    y_scale = ofGetHeight() / num_networks;
    int largest_num_layers = 0;
    for (int i = 0; i < num_networks; i++) {
        if (network[i].num_layers >= largest_num_layers) largest_num_layers = network[i].num_layers;
    }
    for (int i = 0; i < num_networks; i++) {
        Vec2d pos{ 100, y_scale * (i + (double)0.5) };
        network[i].init(pos);
        const int last_indx = network[i].num_layers - 1;
        layer last = network[i].layers[last_indx];
        Vec2d p{pos.x + largest_num_layers * network[i].diff + 200, y_scale * (num_networks/(double)2) - last.scale * ( last.num_neurons * (num_networks/(double)2.0)) + last.scale*(i-1) * last.neuron_size};//divides evenly among the ypos based off number of neurons
        ideals.push_back(layer{ network[i].layers[network[i].num_layers - 1].num_neurons, p});
        ideals[i].init();
        //update last layer's position to be all in front of ideals
        network[i].layers[last_indx].update_pos(Vec2d{ p.x - 200, p.y });
        network[i].layers[0].update_pos(Vec2d{ pos.x, y_scale * (num_networks / double(2)) });

    }
}

void convneuralnet::new_data(int line){
    for (int i = 0; i < num_networks; i++) {
        network[i].new_data(line, &ideals[i]);
    }
}

void convneuralnet::randomize_weights(){
    for (int i = 0; i < num_networks; i++) {
        network[i].randomize_weights();
    }
}

void convneuralnet::comp_avg_cost(){
    avg_cost = 0;
    for (int i = 0; i < num_networks; i++) {
        network[i].comp_avg_cost(&ideals[i]);
        avg_cost += network[i].avg_cost;
    }
    avg_cost /= num_networks;
}

void convneuralnet::avg_improve(){
    for (int i = 0; i < num_networks; i++) {
        std::vector<double> v;
        network[i].avg_improve(&ideals[i], &ideals[i], v);
    }
    comp_avg_cost();
}

void convneuralnet::output(){
    std::ofstream output("output.txt");

    for (int i = 0; i < num_networks; i++) {
        output << "//Network: " << i + 1 << "\n";
        output << network[i].output();
    }
    output.flush();
}

void convneuralnet::draw()
{
    for (int i = 0; i < num_networks; i++) {
        network[i].draw();
        ideals[i].draw();
        drawFontText(network[i].cost, Vec2d(ideals[i].pos.x + 200, ideals[i].pos.y - 30));
        drawFontText(network[i].avg_cost, Vec2d(ideals[i].pos.x + 400, ideals[i].pos.y - 30));
    }
}
