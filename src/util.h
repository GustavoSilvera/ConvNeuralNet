#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <fstream>

#include "ofMain.h"//main OF include for everything... placed here bc everything includes util...
static ofTrueTypeFont font;

static inline float clampf(float min, float max, float i) {
    if (i > min) {
        if (i < max) return i;
        return max;
    }
    return min;
}
inline int sgn(float a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}
inline float sqr(float a) {
    return a * a;
}
class Vec2f {//3d vector used for everything
public:
    Vec2f() : x(0), y(0) {}
    Vec2f(float X, float Y) : x(X), y(Y) {}
    float x, y;
    Vec2f operator*(float f) {
        return Vec2f(x*f, y*f);
    }
    float dist(Vec2f v) {
        return sqrt(sqr(v.x - x) + sqr(v.y - y));
    }
    float dist2(Vec2f v) {//distance squared (optimized)
        return (sqr(v.x - x) + sqr(v.y - y) );
    }
    Vec2f operator+(Vec2f v) {
        return Vec2f(x + v.x, y + v.y);
    }
    Vec2f clamp(float min, float max) {
        float clamped_x = clampf(min, max, x);
        float clamped_y = clampf(min, max, y);
        return Vec2f(clamped_x, clamped_y);
    }
};

class Vec3f {//3d vector used for everything
public:
    Vec3f() : x(0), y(0), z(0) {}
    Vec3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    float x, y, z;
    Vec3f operator*(float f) {
        return Vec3f(x*f, y*f, z*f);
    }
    float dist(Vec3f v) {
        return sqrt(sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    float dist2(Vec3f v) {//distance squared (optimized)
        return (sqr(v.x - x) + sqr(v.y - y) + sqr(v.z - z));
    }
    Vec3f operator+(Vec3f v) {
        return Vec3f(x + v.x, y + v.y, z + v.z);
    }
    Vec3f clamp(float min, float max) {
        float clamped_x = clampf(min, max, x);
        float clamped_y = clampf(min, max, y);
        float clamped_z = clampf(min, max, z);

        return Vec3f(clamped_x, clamped_y, clamped_z);
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
};
static void renderFont(){
    font.loadFont("verdana.ttf", 25);//once per setup renderer
}
static void drawFontText(float text, Vec2f pos) {
    if(!font.isLoaded()) renderFont();
    std::stringstream dummyText;
    std::string PRINT;
    dummyText << text;
    dummyText >> PRINT;
    pos.x += 50;
    font.drawString(PRINT, pos.x, pos.y);
}
#endif // UTIL_H
