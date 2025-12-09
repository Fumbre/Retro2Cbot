// ==========================================

#include "lineSensor.h"

LineSensor::LineSensor(int* pins, int count, int threshold) // constructor of linesensor
    : pins(pins), count(count), threshold(threshold) {} // begin member initializer list

void LineSensor::setup() { // setup pins
    for (int i = 0; i < count; i++) {
        pinMode(pins[i], INPUT);
    }
}

LineReading LineSensor::read() { // start line reading
    LineReading r;
    r.mask = 0; // no sensors triggered yet so initial bitmask is 0b00000000

    for (int i = 0; i < count; i++) { // read sensor value and store in an array
        int reading = analogRead(pins[i]);
        r.values[i] = reading;

        if (reading > threshold) { // if reading higher than threshold assume black, build bitmask
            // A0 = leftmost → highest bit
            r.mask |= (1 << (count - 1 - i));
        }
    }
    
    return r;
}
