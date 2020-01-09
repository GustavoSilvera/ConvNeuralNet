#pragma once

#include "convneuralnet.h"
#include "graph.h"
#include "../ofMain.h"
#include <vector>
#include <thread>
#include <fstream>

class ofApp : public ofBaseApp{
public:
  ofApp() :
    n_x(0, { 3, 4, 2, 1 }, true, 1),//for X: n{3, 4, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 16 {3, 1} 0 layers
    n_y(1, { 3, 2, 4, 1 }, false, 1),//for Y: n{3, 3, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 26
    n_z(2, { 3, 4, 2, 1 }, true, 1),//for Z: n{3, 4, 1} w/ sigmoid, weight_max = 1, thus: avg_cost ~ 5
    g_avgcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 300 }),
    g_marginalcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 50 }, 0.001)
  {}
  void setup();
  void update();
  void draw();
private:
  void keyPressed(int key);
  void windowResized(int w, int h);
  void print_help() const;
  net n_x, n_y, n_z;
  convneuralnet cnn{};

  graph g_avgcost, g_marginalcost;
  // Change screen resolution
  int mScreenWidth, mScreenHeight;
  glm::vec2 corner_fps;
  float init_window_x, init_window_y;
  float new_window_x, new_window_y;

};
