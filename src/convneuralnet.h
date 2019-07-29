#ifndef CONVNEURALNET_H
#define CONVNEURALNET_H

#include "net.h"

class convneuralnet {
public:
    convneuralnet(std::vector<net> n) : network(n) {
        num_networks = n.size();
    }
    std::vector<net> network;
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
    void draw();
};

#endif // CONVNEURALNET_H
