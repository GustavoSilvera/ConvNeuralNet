#include "net.h"

void net::init(vec2 p){
    num_layers = num_neurons.size();
    for (int i = 0; i < num_layers; i++) {
        vec2 layerPos{ p.x + diff * (i + 0.5), p.y };
        layers.push_back(layer{ num_neurons[i], layerPos });
    }
    read_data();
    //hovering colors
    for (int i = 0; i < num_layers; i++) {
        layers[i].init();//init all the layers
        std::vector<vec3> ind_col;//individual colors
        for (int j = 0; j < layers[i].num_neurons; j++) {
            ind_col.push_back(vec3{ 1, 1, 1 });//every node group's colour is initially white
        }
        col.push_back(ind_col);
    }
    //creates random weights
    for (int i = 0; i < num_layers - 1; i++) {//for every (behind) layer [not the last one]
        std::vector<std::vector<double>> ind_neuron;
        for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in said layer
            std::vector<double> ind_neu_weights;//individual weights
            for (int k = 0; k < layers[i + 1].num_neurons; k++) {//for every neuron in the NEXT layer
                int rand_max = int(200 * weight_max);//2 decimal places (pos/neg from weight_max)
                ind_neu_weights.push_back(((rand() % rand_max) / 100.0) - weight_max);//random from -4 to 4
            }
            ind_neuron.push_back(ind_neu_weights);
        }
        weights.push_back(ind_neuron);
    }
    //creates random biases
    for (int i = 1; i < num_layers; i++) {//for every later layer (not the first one)
        std::vector<double> ind_biases;
        for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in said layer
            int rand_max = int(200 * weight_max);//2 decimal places (pos/neg from weight_max)
            ind_biases.push_back(((rand() % rand_max) / 100.0) - weight_max);//individual 'default' biases are 0
        }
        bias.push_back(ind_biases);
    }
}

double net::sigmoid(double x){
    const double e = 2.71828182846;
    return(1 / (1 + pow(e, -x)));
}

double net::smooth_RelU(double x){
    //const double e = 2.71828182846;
    if(x<5)	return log10(1 + exp(x));
    return (0.4337151304 * x + 0.0058131963);
}

const string kRootDir = "/home/gustavo/Documents/projects/openFrameworks/neuralNet/";

void net::read_data(){
#define MAX_LINE 100
    std::ifstream file(kRootDir + "src/DATA_good.txt");
    if(file.is_open()){
        while (!file.eof()) {
            std::vector<double> ind_data;
            char line[MAX_LINE];
            file.getline(line, MAX_LINE);
            char pos_x[MAX_LINE];
            char pos_y[MAX_LINE];
            char pos_z[MAX_LINE];
            char vel_x[MAX_LINE];
            char vel_y[MAX_LINE];
            char vel_z[MAX_LINE];
            sscanf(line, "%s %s %s %s %s %s", pos_x, pos_y, pos_z, vel_x, vel_y, vel_z );
            ind_data.push_back(atof(pos_x));
            ind_data.push_back(atof(pos_y));
            ind_data.push_back(atof(pos_z));
            if(output_variable == 0) ind_data.push_back(atof(vel_x));//for X only
            else if (output_variable == 1) ind_data.push_back(atof(vel_y));//for Y only
            else ind_data.push_back(atof(vel_z));//for Z only
            data.push_back(ind_data);
        }
    }
    else cout << "Unable to open file" << std::getenv("CWD");
}

void net::update_layers(){
    for (int i = 1; i < num_layers; i++) {//only the next layers (last ones)
        std::vector<double> new_values;
        for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in the next layers
            double weighted_sum = 0;
            for (int k = 0; k < layers[i - 1].num_neurons; k++) {//back to every neuron in last layer
                weighted_sum += layers[i - 1].n[k].val * weights[i - 1][k][j];//adds to the weighted sum
            }
            if (i < layers[i].num_neurons - 1) {
                if(usingSigmoid) new_values.push_back(sigmoid(weighted_sum + bias[i - 1][j]));
                else new_values.push_back(smooth_RelU(weighted_sum + bias[i - 1][j]));
            }
            else {
                new_values.push_back(weighted_sum + bias[i - 1][j]);//no sigmoid on last layer (needs to be outputs)
            }
        }
        layers[i].update_value(new_values, bias[i-1]);//bias[0] corresponds to layers[1] & so on
    }
}
void net::comp_avg_cost(layer *opt){
    total_cost = 0;//reset's cost
    num_errors = 1;
    for (int line = 0; line < data.size(); line++) {
        new_data(line, opt);
    }
}

void net::new_data(int line, layer *optimal){
    std::vector<double> new_inputs;
    for (int i = 0; i < layers[0].num_neurons; i++) {
        new_inputs.push_back(data[line][i]);
    }
    layers[0].update_value(new_inputs);//first (input) layer is first updates
    std::vector<double> new_outputs;
    for (int i = layers[0].num_neurons; i < data[line].size(); i++) {//starting where last loop left off
        new_outputs.push_back(data[line][i]);
    }
    optimal->update_value(new_outputs);//optimal (the "should be" output) layer is second
    cost = compute_cost(optimal);
    total_cost += cost;
    num_errors++;
    avg_cost = total_cost / num_errors;
}

double net::compute_cost(layer *optimal){
    double error = 0;
    update_layers();
    for (int i = 0; i < layers[num_layers - 1].num_neurons; i++) {
        error += sqr(layers[num_layers - 1].n[i].val - optimal->n[i].val);
    }
    return error;
}

void net::randomize_weights(){
    for (int i = 0; i < num_layers - 1; i++) {//for every layer (except last one)
        for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in said layer
            for (int k = 0; k < layers[i + 1].num_neurons; k++) {//for every weight its attached to
                weights[i][j][k] = randfrom(weight_max, 2);//new random weight from -4 to 4
                bias[i][k] = randfrom(weight_max, 2);//random biases from -4 to 4
            }
        }
    }
}
net::total_changes net::improve(int i, layer *ideal, vector<double> t_changes){
    //for (int i = num_layers - 1; i > 1; i--) {//for every layer (except first one) (starting from end\output)
    total_changes t;
    std::vector<double> changes;
    if (t_changes.size() == 0) {//basically only for the output layer (same dimens as output-ideal)
        for (int j = 0; j < layers[i].num_neurons; j++) {
            changes.push_back(ideal->n[j].val - layers[i].n[j].val);//difference bw output & ideal
        }
    }
    else {
        for (int j = 0; j < layers[i].num_neurons; j++) {
            double sum = 0;
            for (int k = 0; k < t_changes.size(); k++) {
                sum += weights[i][j][k] * t_changes[k];//adds up all the WEIGHTED changes from the next layer
            }
            changes.push_back(sum/t_changes.size());//average total direction change over t_changes
        }
    }
    for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in said layer
        //compare neuron[i] to ideal_neuron[i];
        const double step = 0.01;
        double bias_change = step * changes[j];
        std::vector<double> ind_mods;
        //increase weight if its neuron is positive, decrease if negative;
        for (int k = 0; k < layers[i-1].num_neurons; k++) {//for every (behind)weight its attached to
            double weight_change = step * changes[j] * (layers[i-1].n[k].val);//proportional difference to the direction of change and neuron value
            //weights[i - 1][k][j] += weight_change;//change weights proportoinal to the error
            ind_mods.push_back(weight_change);
        }
        t.weight_changes.push_back(ind_mods);//what each of the neurons desires its attaching weights to be changed by
        //bias[i - 1][j] += bias_change;//change biases proportoinal to the error
        t.bias_changes.push_back(bias_change);
    }
    return t;
}

void net::avg_improve(layer *ideal, layer *rel_ideal, vector<double> t_changes, int layerInd){
    if (t_changes.size() == 0) layerInd = num_layers - 1;//very first condition
    if (layerInd > 0) {//recursion failsafe (exit condition)
        std::vector<double> tot_changes;
        std::vector<total_changes> changes;
        const int num_changes = data.size();//total number of data sets (lines)
        for (int line = 0; line < num_changes; line++) {//obtain all the desired modifications from every data set
            new_data(line, rel_ideal);
            changes.push_back(improve(layerInd, ideal, t_changes));
        }
        for (int i = 0; i < layers[layerInd].num_neurons; i++) {//all neurons
            double avg_bias = 0;
            for (int j = 0; j < num_changes; j++) {//all data values
                avg_bias += changes[j].bias_changes[i];//add to average (total)
            }
            avg_bias /= num_changes;//divide by how many
            bias[layerInd - 1][i] += avg_bias;//change biases(always 1 less bc starts from output and dosent inclide first layer) by average
            tot_changes.push_back(avg_bias);//first indicator (of change direction) is biases
        }
        for (int i = 0; i < layers[layerInd - 1].num_neurons; i++) {//all neurons in last layer(weights are emitted)
            double avg_weight = 0;
            for (int j = 0; j < layers[layerInd].num_neurons; j++) {//for the individual weight of said neuron
                for (int k = 0; k < num_changes; k++) {//all data values
                    avg_weight += changes[k].weight_changes[j][i];//add to average (total)
                }
                avg_weight /= num_changes;//divide by how many
                weights[layerInd - 1][i][j] += avg_weight;
                //weights[layerInd - 1][i][j] = sigmoid2(weights[layerInd - 1][i][j]);//clamps it
                tot_changes[j] += avg_weight;//second indicator of direction change is total weight changes
            }
        }
        update_layers();
        avg_improve(&layers[layerInd], rel_ideal, tot_changes, layerInd - 1);
    }
    else comp_avg_cost(rel_ideal);//computes total average cost of thee entire net

}

vec3 net::colorGrade(double w){
    double scalar = (255 / weight_max);//weight_max, being the weight's maximum
    double color = abs(scalar * w);
    if(w > 0) return(vec3{0, color, 0 });
    return(vec3{ color, 0, 0 });
}

string net::output(){
    string ret;
    ret.append("//Data: " + std::to_string(output_variable));
    ret.append("; Using: ");
    if (usingSigmoid) ret.append("Sigmoid; ");
    else ret.append("RelU; ");
    ret.append("weight_max: " + std::to_string(weight_max));
    ret.append("; network: {");
    for (int i = 0; i < num_layers; i++) {
        ret.append(std::to_string(layers[i].num_neurons));
        if (i < num_layers - 1) ret.append(", ");//comma to separate the num_neurons
    }
    ret.append("}; \n");
    //print all weights
    ret.append("weights[" + std::to_string(output_variable) + "] = {\n");//open layer
    for (int i = 0; i < num_layers - 1; i++) {
        ret.append("   {\n");//open layer
        for (int j = 0; j < layers[i].num_neurons; j++) {
            ret.append("      {");//open neuron
            for (int k = 0; k < layers[i + 1].num_neurons; k++) {
                ret.append(std::to_string(weights[i][j][k]));
                if (k < layers[i + 1].num_neurons - 1) ret.append(", ");//comma to separate the weights
            }
            ret.append("}");//close neuron
            if (j < layers[i].num_neurons - 1) ret.append(", \n");
            else ret.append("\n");
        }
        ret.append("   },\n");//close layer
    }
    ret.append("};\n");
    //print all the biases
    ret.append("biases[" + std::to_string(output_variable) + "] = {\n");//open layer
    for (int i = 0; i < num_layers - 1; i++) {
        ret.append("   {");//open layer
        for (int j = 0; j < layers[i+1].num_neurons; j++) {
            ret.append(std::to_string(bias[i][j]));
            if (j < layers[i+1].num_neurons - 1) ret.append(", ");//comma to separate the biases
        }
        ret.append("}");//close layer
        if (i < num_layers - 1) ret.append(", \n");
        else ret.append("\n");
    }
    ret.append("};\n");
    return ret;

}

void net::draw()
{
    //draw all the weights
    for (int i = 0; i < num_layers - 1; i++) {//for every layer (except last one)
        for (int j = 0; j < layers[i].num_neurons; j++) {//for every neuron in said layer
            //gl::color(col[i][j].x, col[i][j].y, col[i][j].z);//hovering colors (FIX)
            for (int k = 0; k < layers[i + 1].num_neurons; k++) {
                vec3 ind_col = colorGrade(weights[i][j][k]);//weights
                ofSetColor(int(ind_col.x), int(ind_col.y), int(ind_col.z));//individual colors
                ofDrawLine(
                            float(layers[i].n[j].pos.x),
                            float(layers[i].n[j].pos.y),
                            float(layers[i + 1].n[k].pos.x),
                            float(layers[i + 1].n[k].pos.y)
                        );
            }
        }
    }
    //draw all the layers
    for (int i = 0; i < num_layers; i++) {
        layers[i].draw();//init all the layers
    }
}
