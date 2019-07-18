#pragma once

#include "ofMain.h"
#include "convneuralnet.h"
#include "graph.h"

#include <vector>
#include <fstream>

using namespace std;

class ofApp : public ofBaseApp{
public:
    ofApp() :
            n_x(0, { 3, 4, 1 }, false, 1),//for X: n{3, 4, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 11
            n_y(1, { 3, 2, 1 }, false, 1),//for Y: n{3, 1} w/ smooth_relU, weight_max = 1, thus: avg_cost ~ 30
            n_z(2, { 3, 4, 1 }, true, 1),//for Z: n{3, 4, 1} w/ sigmoid, weight_max = 1, thus: avg_cost ~ 6
            //cnn( {n_x, n_y, n_z} ),//builds the cnn using the previous nets
            g_avgcost(Vec2d{ 1200, 1200 })
        {}
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    net n_x, n_y, n_z;
    convneuralnet cnn{ { n_x, n_y, n_z } };
    int line = 0;
    graph g_avgcost;
    // Change screen resolution
    int mScreenWidth, mScreenHeight;
    Vec2d corner_fps;

    /*
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);*/

};
