#ifndef NET_H
#define NET_H

#include "layer.h"
#include "string"

using namespace std;

class net {
public:
    net(int op_var, vector<int> network, bool sig, int w_max)  {
        output_variable = op_var;
        usingSigmoid = sig;
        weight_max = w_max;
        for (int i = 0; i < network.size(); i++) {
            num_neurons.push_back(network[i]);
        }
        num_layers = num_neurons.size();

    }
    //CNN stuff
    int output_variable;
    bool usingSigmoid;
    double weight_max;
    //rest of stuff
    int num_layers;
    int num_errors = 1;
    vector<int> num_neurons;
    vector<layer> layers;
    vector<vector<Vec3d>> col;//colors of specific node groups
    vector<vector<vector<double>>> weights;//weights from ind. neurons to all neurons in next layer
    vector<vector<vector<double>>> weight_changes;
    vector<vector<double>> bias;//individual neurons's biases
    vector<vector<double>> bias_changes;//individual neurons's biases
    vector<vector<double>> data;// all the data from the txt file
    bool training = false;
    double cost = 0, total_cost = 0, avg_cost = 0;
    const int diff = 300;//300 pixel intervals
    void init(Vec2d p);
    double sigmoid(double x);
    double smooth_RelU(double x);
    void read_data();
    void update_layers();
    void comp_avg_cost(layer* opt);
    void new_data(int line, layer* optimal);
    double compute_cost(layer* optimal);
    void randomize_weights();
    struct total_changes {
        std::vector<std::vector<double>> weight_changes;
        std::vector<double> bias_changes;
    };
    total_changes improve(int i, layer* ideal, vector<double> t_changes);
    void avg_improve(layer* ideal, layer* rel_ideal, vector<double> t_changes, int layerInd = 0);
    Vec3d colorGrade(double w);
    string output();
    void draw();
};
#endif // NET_H
