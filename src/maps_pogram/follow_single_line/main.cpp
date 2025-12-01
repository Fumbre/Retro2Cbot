// #include "common/robot/movement/movement.h"
// #include "lineSensor.h"
// #include "lineFollower.h"

// int pins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// LineSensor sensor(pins, 8, 700);
// LineFollower follower(60, 70);  // base, turn

// void setup() {
//     Serial.begin(9600);
//     setupMotor();
//     sensor.setup();
// }

// void loop() {
//     follower.follow(sensor);
// }

// ================================================

#include <Arduino.h>
#include "common/robot/movement/movement.h"
#include "lineSensor.h"
#include "lineInterpreter.h"
#include "lineFollower.h"

int sensorPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };

LineSensor sensor(sensorPins, 8, 700);
LineInterpreter interpreter;
LineFollower follower(190, 250);

void setup() {
    Serial.begin(9600);
    setupMotor();
    sensor.setup();
}

void loop() {
    follower.follow(sensor, interpreter);
}
