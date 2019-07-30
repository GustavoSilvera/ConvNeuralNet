#ifndef CONVNEURALNET_H
#define CONVNEURALNET_H

#include "net.h"

class convneuralnet {
public:
    convneuralnet(std::vector<net> n) : network(n) {
        num_networks = n.size();
        read_data();
        init();
    }
    convneuralnet(){
        read_data();
        std::vector<std::vector<int>> inner_layers {{4, 2}, {3, 4}, {4, 2}};
        std::vector<bool> using_sigmoid {true, false, true};
        std::vector<int> maximum_weights{1, 1, 1};
        std::vector<std::vector<int>> final_layers;
        std::vector<net> n;
        for(int i = 0; i < num_inputs[i]; i++){//for all inputs (should be same accross all 'i')
            std::vector<int> ind_layer{num_inputs[i]};
            for(int j = 0; j < inner_layers[i].size(); j++){
                ind_layer.push_back(inner_layers[i][j]);
            }
            ind_layer.push_back(1);//final (output) layer
            final_layers.push_back(ind_layer);
        }
        for(int i = 0; i < num_inputs[i]; i++){
            net new_n{i, final_layers[i], using_sigmoid[i], maximum_weights[i]};
            n.push_back(new_n);
        }
        num_networks = n.size();
        network.swap(n);//update local network
        init();
    }
    std::vector<net> network;
    std::vector<std::vector<vec2>> network_pos, init_pos;
    std::vector<layer> ideals;
    std::vector<std::vector<double>> total_data;//single large dataset of all i/o
    std::vector<int> num_inputs, num_outputs;
    int num_networks;
    double y_scale;
    double avg_cost, last_cost;//last_cost used to compute marginal
    bool training = false;
    void init();
    //void update_pos(int x, int y);
    void read_data();
    void new_data();
    void randomize_weights();
    void comp_avg_cost();
    void avg_improve();
    void output();
    void resize(vec2 init, vec2 current);
    void draw();
};

#endif // CONVNEURALNET_H
