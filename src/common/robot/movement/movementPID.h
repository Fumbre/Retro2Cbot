#pragma once
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/constant/motor.h"
#include "common/robot/motor/motor.h"
#include "common/constant/robot.h"
#include "common/tools/timer.h"
#include "common/tools/PID.h"

extern float integral;

void moveForward(int speed);

void moveBackward(int speed);

void switchDirection(int leftSpeed, int rightSpeed);

void stopMotors();

float getPWMvalue(int speed);

Stability adjustPWMvalueByPulse(float *leftPWMValue, float *rightPWMValue);

void rotateLeft(int speed);
void rotateRight(int speed);