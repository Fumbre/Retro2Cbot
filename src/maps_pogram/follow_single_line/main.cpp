// ================================================

// #include <Arduino.h>
// #include "common/robot/movement/movement.h"
// #include "lineSensor.h"
// #include "lineInterpreter.h"
// #include "lineFollower.h"
// #include "lineFollowerLogic.h"

// int sensorPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };

// LineSensor sensor(sensorPins, 8, 700);
// LineInterpreter interpreter;

// LineFollower follower(200,255);
// LineFollowerLogic logic(200,255);


// void setup() {
//     Serial.begin(9600);
//     setupMotor();
//     sensor.setup();
// }


// void loop() {
//     MotorCommand cmd = follower.follow(sensor, interpreter, logic);
//     moveSpeed(cmd.left, cmd.right);
// }

