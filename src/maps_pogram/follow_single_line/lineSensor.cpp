// #include "lineSensor.h"

// LineSensor::LineSensor(int* pins, int count, int threshold)
//   : pins(pins), count(count), threshold(threshold) {}

// void LineSensor::setup() {
//     for (int i = 0; i < count; i++) pinMode(pins[i], INPUT);
// }

// LineReading LineSensor::read() {
//     LineReading r;
//     r.mask = 0;

//     for (int i = 0; i < count; i++) {
//         int value = analogRead(pins[i]);
//         r.values[i] = value;

//         // black = HIGH (your sensors)
//         if (value > threshold) {
//             r.mask |= (1 << (count - 1 - i)); // A0=left => bit7
//         }
//     }

//     return r;
// }


// ==========================================

#include "lineSensor.h"

LineSensor::LineSensor(int* pins, int count, int threshold)
    : pins(pins), count(count), threshold(threshold) {}

void LineSensor::setup() {
    for (int i = 0; i < count; i++) {
        pinMode(pins[i], INPUT);
    }
}

LineReading LineSensor::read() {
    LineReading r;
    r.mask = 0;

    for (int i = 0; i < count; i++) {
        int reading = analogRead(pins[i]);
        r.values[i] = reading;

        if (reading > threshold) {
            // A0 = leftmost → highest bit
            r.mask |= (1 << (count - 1 - i));
        }
    }

    return r;
}
