#ifndef UTIL_H
#define UTIL_H

#include "/home/gustavo/OF/libs/openFrameworks/ofMain.h"//main OF include for everything... placed here bc everything includes util...


#include <math.h>
#include <fstream>

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
