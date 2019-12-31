#pragma once
#include "convneuralnet.h"
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

class ofApp{
public:
  ofApp() :
    n_x(0, { 3, 4, 2, 1 }, true, 1),//for X: n{3, 4, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 16 {3, 1} 0 layers
    n_y(1, { 3, 4, 2, 1 }, false, 1),//for Y: n{3, 3, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 26
    n_z(2, { 3, 4, 2, 1 }, true, 1)//for Z: n{3, 4, 1} w/ sigmoid, weight_max = 1, thus: avg_cost ~ 5
  {}
  void setup();
  void update();
  
  net n_x, n_y, n_z;
  convneuralnet cnn{};
};
