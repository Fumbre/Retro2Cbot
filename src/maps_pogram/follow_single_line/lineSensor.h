// ========================================

#pragma once
#include <Arduino.h>

struct LineReading {
    uint8_t mask;
    int values[8];
};

class LineSensor {
public:
    LineSensor(int* pins, int count, int threshold);

    void setup();
    LineReading read();

private:
    int* pins;
    int count;
    int threshold;
};
