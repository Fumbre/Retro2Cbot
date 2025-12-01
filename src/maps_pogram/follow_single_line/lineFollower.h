// #pragma once
// #include <Arduino.h>
// #include "lineSensor.h"

// class LineFollower {
// public:
//     LineFollower(int baseSpeed, int turnSpeed);

//     void follow(LineSensor& sensor);

// private:
//     int baseSpeed;
//     int turnSpeed;
// };


// =================================================

#pragma once
#include "lineSensor.h"
#include "lineInterpreter.h"

class LineFollower {
public:
    LineFollower(int baseSpeed, int turnSpeed);

    void follow(LineSensor& sensor, LineInterpreter& interpreter);

private:
    int baseSpeed;
    int turnSpeed;
};
