// #pragma once
// #include <Arduino.h>
// #include "common/constant/motor.h"
// #include "common/robot/motor/motor.h"

// void moveForward(int speed);
// void moveBackward(int speed);
// void moveRight(int speed);
// void moveLeft(int speed);

// void rotateLeft(int speed);
// void rotateRight(int speed);

// void moveStop(int wheel_pin);
// void moveStopAll();

#pragma once
#include <Arduino.h>
#include "common/constant/motor.h"
#include "common/robot/motor/motor.h"
#include "common/constant/robot.h"

void moveForward(int speed);

void moveBackward(int speed);

void switchDirection(int leftSpeed, int rightSpeed);

void stopMotors();

int getPWMvalue(int speed);

void rotate(int speed, String direction, float angle);

void adjustPWMvalueByPulse(int &leftPWMValue, int &rightPWMValue);