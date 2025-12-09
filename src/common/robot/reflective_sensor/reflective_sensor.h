#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"

struct Stats
{
  unsigned long count = 0;
  double mean = 0.0;
  double m2 = 0.0; // sum of squares of differences for variance
  int minimum = 1023;
  int maximum = 0;
  void update(int x)
  {
    count++;
    double dx = x - mean;
    mean += dx / count;
    double dx2 = x - mean;
    m2 += dx * dx2;
    if (x < minimum)
      minimum = x;
    if (x > maximum)
      maximum = x;
  }
};

Stats *getRSValue();
int *getLineStatus();

void setupRS();