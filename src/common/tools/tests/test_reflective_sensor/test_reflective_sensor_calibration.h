#pragma once
#include <Arduino.h>

void loopRs();
void setupRs();

struct Stats {
  unsigned long count = 0;
  double mean = 0.0;
  double m2 = 0.0; // sum of squares of differences for variance
  int minimum = 1023;
  int maximum = 0;
  void update(int x) {
    count++;
    double dx = x - mean;
    mean += dx / count;
    double dx2 = x - mean;
    m2 += dx * dx2;
    if (x < minimum) minimum = x;
    if (x > maximum) maximum = x;
  }
  double variance() const { return (count > 1) ? (m2 / (count - 1)) : 0.0; }
  double stddev()  const { return sqrt(variance()); }
};
