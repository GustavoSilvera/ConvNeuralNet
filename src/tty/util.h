#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <fstream>

static inline double clampd(double min, double max, double i)
{
  if (i > min)
  {
    if (i < max)
      return i;
    return max;
  }
  return min;
}

inline int sgn(double a)
{
  if (a > 0)
    return 1;
  if (a < 0)
    return -1;
  return 0;
}

inline double sqr(double a)
{
  return a * a;
}

inline double max(const double a, const double b)
{
  if (a > b)
    return a;
  return b;
}

inline size_t randint(size_t min, size_t max)
{
  return size_t((rand() % (max - min)) + 1) + min;
}

inline double randfrom(double range, int decimals = 2)
{
  double tens_place = pow(10, decimals);
  int rand_max = int(2 * tens_place * range);               //n decimal places (pos/neg from range)
  return (((std::rand() % rand_max) / tens_place) - range); //new random weight from -range to range
}

#endif // UTIL_H
