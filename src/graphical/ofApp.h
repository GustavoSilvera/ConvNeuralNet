#pragma once

#include "convneuralnet.h"
#include "graph.h"
#include "../ofMain.h"
#include <vector>
#include <thread>
#include <fstream>

class ofApp : public ofBaseApp
{
public:
  ofApp() : g_avgcost(vec2{ofGetWidth() - 800, ofGetHeight() - 300}),
            g_marginalcost(vec2{ofGetWidth() - 800, ofGetHeight() - 50}, 0.001)
  {                    //takes internal network data
    read_first_line(); //initialized num_inputs/outputs
    if (num_inputs == 0 || num_outputs == 0)
      throw std::exception();
    std::vector<std::vector<size_t>> num_layer_neurons;
    for (size_t i = 0; i < num_inputs; i++)
    { //for each network
      //randomly generate internal layers
      std::vector<size_t> num_neurons;
      const size_t num_layers = randint(1, 3); //min of 1 layer, max of 3
      for (size_t j = 0; j < num_layers; j++)
      {
        num_neurons.push_back(randint(1, 5)); //each layer can have 0-5 neurons
      }
      num_layer_neurons.push_back(num_neurons);
    }
    for (size_t i = 0; i < num_inputs; i++)
    {
      std::vector<size_t> layer_neurons = {num_inputs}; //initialized w/ num inputs
      const size_t num_layers = num_layer_neurons[i].size();
      for (size_t j = 0; j < num_layers; j++)
      {
        layer_neurons.push_back(num_layer_neurons[i][j]); //internal layer data
      }
      layer_neurons.push_back(1); //each net focuses on a single output
      bool using_sig = true;
      if (randint(0, 1) == 1)
        using_sig = false;
      nets.emplace_back(i, layer_neurons, using_sig, randint(1, 2)); //add to vector of nets
    }
    //random network
    cnn.set_nets(nets); //custom constructor
  }
  /*ofApp() ://hardcoded
    n_x(0, { 3, 4, 2, 1 }, true, 1),//for X: n{3, 4, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 16 {3, 1} 0 layers
    n_y(1, { 3, 2, 4, 1 }, false, 1),//for Y: n{3, 3, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 26
    n_z(2, { 3, 4, 2, 1 }, true, 1),//for Z: n{3, 4, 1} w/ sigmoid, weight_max = 1, thus: avg_cost ~ 5
    g_avgcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 300 }),
    g_marginalcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 50 }, 0.001)
  {
    cnn{};//default constructor
    }*/
  void setup();
  void update();
  void draw();

private:
  void keyPressed(int key);
  void windowResized(int w, int h);
  void print_help() const;
  void randomize_nets();
  void read_first_line();
  std::vector<net> nets;
  convneuralnet cnn;
  size_t num_inputs, num_outputs;
  graph g_avgcost, g_marginalcost;
  // Change screen resolution
  int mScreenWidth, mScreenHeight;
  glm::vec2 corner_fps;
  float init_window_x, init_window_y;
  float new_window_x, new_window_y;
};
