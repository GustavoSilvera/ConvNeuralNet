#pragma once

#include "ofMain.h"
#include "convneuralnet.h"
#include "graph.h"

#include <vector>
#include <thread>
#include <fstream>

using namespace std;

class ofApp : public ofBaseApp{
public:
    ofApp() :
            n_x(0, { 3, 4, 2, 1}, true, 1),//for X: n{3, 4, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 16 {3, 1} 0 layers
            n_y(1, { 3, 3, 4, 1 }, false, 1),//for Y: n{3, 3, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 26
            n_z(2, { 3, 4, 2, 1 }, true, 1),//for Z: n{3, 4, 1} w/ sigmoid, weight_max = 1, thus: avg_cost ~ 5

            //cnn( {n_x, n_y, n_z} ),//builds the cnn using the previous nets
            g_avgcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 300 }),
            g_marginalcost(vec2{ ofGetWidth() - 800, ofGetHeight() - 50 }, 0.001)
        {}
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void windowResized(int w, int h);

    net n_x, n_y, n_z;
    convneuralnet cnn{ { n_x, n_y, n_z} };
    int line = 0;
    graph g_avgcost, g_marginalcost;
    // Change screen resolution
    int mScreenWidth, mScreenHeight;
    vec2 corner_fps;
    float init_window_x, init_window_y;
    float new_window_x, new_window_y;
    /*
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);*/

};
