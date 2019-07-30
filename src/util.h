#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <fstream>

#include "ofMain.h"//main OF include for everything... placed here bc everything includes util...
static ofTrueTypeFont font;
using namespace glm;
static inline double clampd(double min, double max, double i) {
    if (i > min) {
        if (i < max) return i;
        return max;
    }
    return min;
}
inline int sgn(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}
inline double sqr(double a) {
    return a * a;
}
inline double randfrom(double range, int decimals = 2){
    double tens_place = pow(10, decimals);
    int rand_max = int(2 * tens_place * range);//n decimal places (pos/neg from range)
    return (((rand() % rand_max ) / tens_place ) - range);//new random weight from -range to range
}
/*
class Vec2d {//3d vector used for everything
public:
    Vec2d() : x(0), y(0) {}
    Vec2d(double X, double Y) : x(X), y(Y) {}
    double x, y;
    Vec2d operator*(double f) {
        return Vec2d(x*f, y*f);
    }
    double dist(Vec2d v) {
        return sqrt(sqr(v.x - x) + sqr(v.y - y));
    }
    double dist2(Vec2d v) {//distance squared (optimized)
        return (sqr(v.x - x) + sqr(v.y - y) );
    }
    Vec2d operator+(Vec2d v) {
        return Vec2d(x + v.x, y + v.y);
    }
    Vec2d clamp(double min, double max) {
        double clamped_x = clampd(min, max, x);
        double clamped_y = clampd(min, max, y);
        return Vec2d(clamped_x, clamped_y);
    }
};

class Vec3d {//3d vector used for everything
public:
    Vec3d() : x(0), y(0), z(0) {}
    Vec3d(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    double x, y, z;
    Vec3d operator*(double f) {
        return Vec3d(x*f, y*f, z*f);
    }
    double dist(Vec3d v) {
        return sqrt(sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    double dist2(Vec3d v) {//distance squared (optimized)
        return (sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    Vec3d operator+(Vec3d v) {
        return Vec3d(x + v.x, y + v.y, z + v.z);
    }
    Vec3d clamp(double min, double max) {
        double clamped_x = clampd(min, max, x);
        double clamped_y = clampd(min, max, y);
        double clamped_z = clampd(min, max, z);

        return Vec3d(clamped_x, clamped_y, clamped_z);
    }
};

template<typename T>
class vec3 {//3d vector used for everything
public:
    vec3() : x(0), y(0), z(0) {}
    vec3(T X = 0.0, T Y = 0.0, T Z = 0.0) : x(X), y(Y), z(Z) {}
    T x, y, z;
    vec3 operator*(T f) {
        return vec3(x*f, y*f, z*f);
    }
    T dist(vec3 v) {
        return sqrt(sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    T dist2(vec3 v) {//distance squared (optimized)
        return (sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    vec3 operator+(vec3 v) {
        return vec3(x + v.x, y + v.y, z + v.z);
    }
    vec3 clamp(T min, T max) {
        return vec3(clamp(min, max, x), clamp(min, max, y), clamp(min, max, z));
    }
};*/
static void renderFont(int size){
    font.load("verdana.ttf", size);//loading font at specific size
}
static void drawFontText(double text, vec2 pos, int size = 25) {
    if(!font.isLoaded()) renderFont(size);
    std::stringstream dummyText;
    std::string PRINT;
    dummyText << setprecision(4) << text;
    dummyText >> PRINT;
    pos.x += 35;
    font.drawString(PRINT, float(pos.x), float(pos.y));
}
#endif // UTIL_H
