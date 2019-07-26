#include "convneuralnet.h"



void convneuralnet::init(){
    y_scale = ofGetHeight() / num_networks;//divides the window width to the number of neural nets
    int largest_num_layers = 0;//the "num_layers" of the largest neural net
    for (int i = 0; i < num_networks; i++) {
        if (network[i].num_layers >= largest_num_layers) largest_num_layers = network[i].num_layers;
    }//simply finds the num_layers of the largest neural net
    for (int i = 0; i < num_networks; i++) {
        vec2 pos{ 100, y_scale * (i + 0.5) };//init x = 100, (i+0.5) to not start top neural net at VERY top of window
        network[i].init(pos);//create network[i]
        const int last_indx = network[i].num_layers - 1;//index of final layer (layers.size() - 1)
        layer last = network[i].layers[last_indx];//copy the last (output) layer of the network
        vec2 p{
            pos.x + largest_num_layers * network[i].diff + 200,//x position for 'ideals' neuron layer
            y_scale * (num_networks/2.0) - last.scale * ( last.num_neurons * (num_networks/2.0)) + last.scale*(i-1) * last.neuron_size
        };//divides evenly among the ypos based off number of neurons
        ideals.push_back(layer{ network[i].layers[network[i].num_layers - 1].num_neurons, p});
        ideals[i].init();
        //update last layer's position to be all in front of ideals
        network[i].layers[last_indx].update_pos(vec2{ p.x - 200, p.y });
        network[i].layers[0].update_pos(vec2{ pos.x, y_scale * (num_networks / 2.0) });

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
    last_cost = avg_cost;
    avg_cost = 0;
    for (int i = 0; i < num_networks; i++) {
        network[i].comp_avg_cost(&ideals[i]);
        avg_cost += network[i].avg_cost;
    }
    avg_cost /= num_networks;
}

static void avg_improve_thread(net* network, layer* ideal){
    std::vector<double> v;
    network->avg_improve(ideal, ideal, v);
}
void convneuralnet::avg_improve(){
    std::vector<std::thread> threads;
    for(int i = 0; i < num_networks; i++){
        //threads.push_back(std::thread(avg_improve_thread, &network[i], &ideals[i]));
        threads.push_back(std::thread([&, i]{
            std::vector<double> v;
            network[i].avg_improve(&ideals[i], &ideals[i], v);
        }));
    }
    //for(int i = 0; i < num_networks; i++){
    //    threads[i].join();
    //}
    for (auto &thread:threads) {
        thread.join();
    }
        //std::thread top (network[0].avg_improve, &ideals[0], &ideals[0], v);
    /*for (int i = 0; i < num_networks; i++) {
       network[i].avg_improve(&ideals[i], &ideals[i], v);
    }*/
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
        drawFontText(network[i].cost, vec2(ideals[i].pos.x + 200, ideals[i].pos.y - 30));
        drawFontText(network[i].avg_cost, vec2(ideals[i].pos.x + 400, ideals[i].pos.y - 30));
    }
}
