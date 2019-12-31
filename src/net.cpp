#include "net.h"
#include <iostream>

using namespace std;

size_t net::get_num_layers() const{
  return num_layers;
}
double net::get_avg_cost() const{
  return avg_cost;
}
const layer& net::get_layer(size_t i) const{
  if(i >= layers.size()) printf("BAD LAYER %zu %zu %zu", i, layers.size(), num_layers);
  return layers[i];
}
void net::init(vector<vector<double>> total_data, vector<size_t> num_inputs){
  for (size_t i = 0; i < num_layers; i++) {
    //creates the layers of the network
    layers.emplace_back(num_neurons[i]);
  }
  total_data_lines = size_t(total_data.size());
  extract_data(total_data, num_inputs);
  //hovering colors
  for (layer& L : layers) {
    L.init_rand();//initialize all the layers randomly
  }
  //creates random weights
  for (size_t i = 0; i < num_layers - 1; i++) {//for every (behind) layer [not the last one]
    vector<vector<double>> ind_neuron;
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {//for every neuron in said layer
      vector<double> ind_neuron_weights;
      for (size_t k = 0; k < layers[i + 1].get_num_neurons(); k++) {//for every neuron in the NEXT layer
	int rand_max = int(200 * weight_max);//2 decimal places (pos/neg from weight_max)
	ind_neuron_weights.push_back(((rand() % rand_max) / 100.0) - weight_max);
      }
      ind_neuron.push_back(ind_neuron_weights);
    }
    weights.push_back(ind_neuron);
  }
  //creates random biases
  for (size_t i = 1; i < num_layers; i++) {//for every later layer (not the first one)
    vector<double> ind_biases;
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {//for every neuron in said layer
      int rand_max = int(200 * weight_max);//2 decimal places (pos/neg from weight_max)
      ind_biases.push_back(((rand() % rand_max) / 100.0) - weight_max);//individual 'default' biases are 0
    }
    bias.push_back(ind_biases);
  }
}
void net::extract_data(vector<vector<double>> total_data, vector<size_t> num_inputs){
  for(size_t i = 0; i < total_data_lines; i++){
    vector<double> ind_line_data;
    for(size_t j = 0; j < num_inputs[i]; j++){//num_inputs[i] has index for all data (lines') individual num_inputs (should all be same)
      ind_line_data.push_back(total_data[i][j]);
    }
    for(size_t j = num_inputs[i]; j < total_data[j].size(); j++){//scans through all (OUTPUT) elements in total_data set
      if(j - num_inputs[i] == focus_variable){//should only happen once
	ind_line_data.push_back(total_data[i][j]);//adds respective "focus" variable
      }
    }
    data.push_back(ind_line_data);
  }
}
double net::sigmoid(double x){
  const double e = 2.718282;
  return(1 / (1 + pow(e, -x)));
}

double net::smooth_RelU(double x){
  //const double e = 2.71828182846;
  if(x<5) return log10(1 + exp(x));
  return (0.4337151304 * x + 0.0058131963);//linear approx
}


void net::update_layers(){
  for (size_t i = 1; i < num_layers; i++) {//only the next layers (last ones)
    vector<double> new_values;
    const size_t layer_num_neurons = layers[i].get_num_neurons();
    for (size_t j = 0; j < layer_num_neurons; j++) {//for every neuron in the next layers
      double weighted_sum = 0;
      const size_t prev_layer_num_neurons = layers[i - 1].get_num_neurons();
      for (size_t k = 0; k < prev_layer_num_neurons; k++) {//back to every neuron in last layer
	double weight_k = layers[i-1].get_neuron(k).get_weight();
	weighted_sum += weight_k * weights[i - 1][k][j];//adds to the weighted sum
      }
      if (i < layer_num_neurons - 1) {
	if(using_sigmoid) new_values.push_back(sigmoid(weighted_sum + bias[i - 1][j]));
	else new_values.push_back(smooth_RelU(weighted_sum + bias[i - 1][j]));
      }
      else {
	new_values.push_back(weighted_sum + bias[i - 1][j]);//no sigmoid on last layer (needs to be outputs)
      }
    }
    layers[i].update_weights(new_values);//bias[0] corresponds to layers[1] & so on
  }
}
void net::comp_avg_cost(layer *opt){
  total_cost = 0;//reset's cost
  num_errors = 1;
  for (size_t line = 0; line < total_data_lines; line++) {
    new_data(opt);//runs new_data to compute errors
  }
}

void net::new_data(layer *optimal){
  if(data_line >= total_data_lines) data_line = 0;//resets after a cycle
  vector<double> new_inputs;
  for (size_t i = 0; i < layers[0].get_num_neurons(); i++) {//first .num_neuron elements in data[] is inputs
    new_inputs.push_back(data[data_line][i]);
  }
  layers[0].update_weights(new_inputs);//first (input) layer is first updates
  vector<double> new_outputs;
  for (size_t i = layers[0].get_num_neurons(); i < data[data_line].size(); i++) {//starting where last loop left off
    new_outputs.push_back(data[data_line][i]);
  }
  optimal->update_weights(new_outputs);//optimal (the "should be" output) layer is second
  cost = compute_cost(optimal);
  total_cost += cost;
  num_errors++;
  data_line++;//next line (next time)
  avg_cost = total_cost / num_errors;
}

void net::test_data(layer *optimal){
  if(data_line >= total_data_lines) data_line = 0;//resets after a cycle
  vector<double> new_inputs;
  for (size_t i = 0; i < layers[0].get_num_neurons(); i++) {//first .num_neuron elements in data[] is inputs
    new_inputs.push_back(data[data_line][i]);
  }
  layers[0].update_weights(new_inputs);//first (input) layer is first updates
  vector<double> new_outputs;
  for (size_t i = layers[0].get_num_neurons(); i < data[data_line].size(); i++) {//starting where last loop left off
    new_outputs.push_back(data[data_line][i]);
  }
  update_layers();
  optimal->update_weights(new_outputs);//optimal (the "should be" output) layer is second
  data_line++;//next line (next time)
}

double net::compute_cost(layer *optimal){
  double error = 0;
  update_layers();
  for (size_t i = 0; i < layers[num_layers - 1].get_num_neurons(); i++) {
    error += sqr(layers[num_layers - 1].get_neuron(i).get_weight() - optimal->get_neuron(i).get_weight());
  }
  return error;
}

void net::randomize_weights(){
  for (size_t i = 0; i < num_layers - 1; i++) {//for every layer (except last one)
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {//for every neuron in said layer
      for (size_t k = 0; k < layers[i + 1].get_num_neurons(); k++) {//for every weight its attached to
	weights[i][j][k] = randfrom(weight_max, 2);//new random weight from -4 to 4
	bias[i][k] = randfrom(weight_max, 2);//random biases from -4 to 4
      }
    }
  }
}
net::total_changes net::improve(int i, layer *ideal, vector<double> t_changes){
  //for (int i = num_layers - 1; i > 1; i--) {//for every layer (except first one) (starting from end\output)
  total_changes t;
  vector<double> changes;
  if (t_changes.size() == 0) {//basically only for the output layer (same dimens as output-ideal)
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {
      changes.push_back(ideal->get_neuron(j).get_weight() - layers[i].get_neuron(j).get_weight());//difference bw output & ideal
    }
  }
  else {
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {
      double sum = 0;
      for (size_t k = 0; k < t_changes.size(); k++) {
	sum += weights[i][j][k] * t_changes[k];//adds up all the WEIGHTED changes from the next layer
      }
      //assert t_changes > 0
      changes.push_back(sum/t_changes.size());//average total direction change over t_changes
    }
  }
  for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {//for every neuron in said layer
    //compare neuron[i] to ideal_neuron[i];
    const double step = 0.001;
    double bias_change = step * changes[j];
    vector<double> ind_mods;
    //increase weight if its neuron is positive, decrease if negative;
    for (size_t k = 0; k < layers[i-1].get_num_neurons(); k++) {//for every (behind)weight its attached to
      double weight_change = step * changes[j] * (layers[i-1].get_neuron(k).get_weight());//proportional difference to the direction of change and neuron value
      //weights[i - 1][k][j] += weight_change;//change weights proportoinal to the error
      ind_mods.push_back(weight_change);
    }
    t.weight_changes.push_back(ind_mods);//what each of the neurons desires its attaching weights to be changed by
    //bias[i - 1][j] += bias_change;//change biases proportoinal to the error
    t.bias_changes.push_back(bias_change);
  }
  return t;
}

void net::avg_improve(layer *ideal, layer *rel_ideal, vector<double> t_changes, size_t layerInd){
  if (t_changes.size() == 0) layerInd = num_layers - 1;//very first condition
  if (layerInd > 0) {//recursion failsafe (exit condition)
    vector<double> tot_changes;
    vector<total_changes> changes;
    const size_t num_changes = data.size();//total number of data sets (lines)
    for (size_t line = 0; line < num_changes; line++) {//obtain all the desired modifications from every data set
      new_data(rel_ideal);
      changes.push_back(improve(layerInd, ideal, t_changes));
    }
    for (size_t i = 0; i < layers[layerInd].get_num_neurons(); i++) {//all neurons
      double avg_bias = 0;
      for (size_t j = 0; j < num_changes; j++) {//all data values
	avg_bias += changes[j].bias_changes[i];//add to average (total)
      }
      avg_bias /= num_changes;//divide by how many
      bias[layerInd - 1][i] += avg_bias;//change biases(always 1 less bc starts from output and dosent inclide first layer) by average
      tot_changes.push_back(avg_bias);//first indicator (of change direction) is biases
    }
    for (size_t i = 0; i < layers[layerInd - 1].get_num_neurons(); i++) {//all neurons in last layer(weights are emitted)
      for (size_t j = 0; j < layers[layerInd].get_num_neurons(); j++) {//for the individual weight of said neuron
	double avg_weight = 0;
	for (size_t k = 0; k < num_changes; k++) {//all data values
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


string net::output() const{
  string ret;
  ret.append("//Data: " + to_string(focus_variable));
  ret.append("; Using: ");
  if (using_sigmoid) ret.append("Sigmoid; ");
  else ret.append("RelU; ");
  ret.append("weight_max: " + to_string(weight_max));
  ret.append("; network: {");
  for (size_t i = 0; i < num_layers; i++) {
    ret.append(to_string(layers[i].get_num_neurons()));
    if (i < num_layers - 1) ret.append(", ");//comma to separate the num_neurons
  }
  ret.append("}; \n");
  //print all weights
  ret.append("weights[" + to_string(focus_variable) + "] = {\n");//open layer
  for (size_t i = 0; i < num_layers - 1; i++) {
    ret.append("   {\n");//open layer
    for (size_t j = 0; j < layers[i].get_num_neurons(); j++) {
      ret.append("      {");//open neuron
      for (size_t k = 0; k < layers[i + 1].get_num_neurons(); k++) {
	ret.append(to_string(weights[i][j][k]));
	if (k < layers[i + 1].get_num_neurons() - 1) ret.append(", ");//comma to separate the weights
      }
      ret.append("}");//close neuron
      if (j < layers[i].get_num_neurons() - 1) ret.append(", \n");
      else ret.append("\n");
    }
    ret.append("   },\n");//close layer
  }
  ret.append("};\n");
  //print all the biases
  ret.append("biases[" + to_string(focus_variable) + "] = {\n");//open layer
  for (size_t i = 0; i < num_layers - 1; i++) {
    ret.append("   {");//open layer
    for (size_t j = 0; j < layers[i+1].get_num_neurons(); j++) {
      ret.append(to_string(bias[i][j]));
      if (j < layers[i+1].get_num_neurons() - 1) ret.append(", ");//comma to separate the biases
    }
    ret.append("}");//close layer
    if (i < num_layers - 1) ret.append(", \n");
    else ret.append("\n");
  }
  ret.append("};\n");
  return ret;

}
