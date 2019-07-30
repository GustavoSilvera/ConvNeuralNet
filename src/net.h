#ifndef NET_H
#define NET_H

#include "layer.h"
#include "string"

using namespace std;

class net {
public:
    net(int focus_var, vector<int> network, bool sig, int w_max)  {
        focus_variable = focus_var;
        usingSigmoid = sig;
        weight_max = w_max;
        for (int i = 0; i < network.size(); i++) {
            num_neurons.push_back(network[i]);
        }
        num_layers = num_neurons.size();
    }
    //CNN stuff
    int focus_variable;
    bool usingSigmoid;
    double weight_max;
    //rest of stuff
    int num_layers;
    int num_errors = 1;
    vector<int> num_neurons;
    vector<layer> layers;
    vector<vector<vec3>> col;//colors of specific node groups
    vector<vector<vector<double>>> weights;//weights from ind. neurons to all neurons in next layer
    vector<vector<vector<double>>> weight_changes;
    vector<vector<double>> bias;//individual neurons's biases
    vector<vector<double>> bias_changes;//individual neurons's biases
    vector<vector<double>> data;// all the data from the txt file
    bool training = false;
    double cost = 0, total_cost = 0, avg_cost = 0;
    const int diff = 200;//300 pixel intervals
    void init(vec2 p, std::vector<std::vector<double>> total_data, std::vector<int> num_inputs);
    int total_data_lines;
    int data_line = 0;
    void extract_data(std::vector<std::vector<double>> total_data, std::vector<int> num_inputs);
    double sigmoid(double x);
    double smooth_RelU(double x);
    void update_layers();
    void comp_avg_cost(layer* opt);
    void new_data(layer* optimal);
    double compute_cost(layer* optimal);
    void randomize_weights();
    struct total_changes {
        std::vector<std::vector<double>> weight_changes;
        std::vector<double> bias_changes;
    };
    total_changes improve(int i, layer* ideal, vector<double> t_changes);
    void avg_improve(layer* ideal, layer* rel_ideal, vector<double> t_changes, int layerInd = 0);
    vec3 colorGrade(double w);
    string output();
    void draw();
};
#endif // NET_H
