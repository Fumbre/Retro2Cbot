#pragma once
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/constant/motor.h"
#include "common/robot/motor/motor.h"
#include "common/constant/robot.h"
#include "common/tools/PID.h"
#include "common/robot/globalvariable/globalVariable.h"

extern float integral;

void moveForward(int speed);
void moveBackward(int speed);
void switchDirection(int leftSpeed, int rightSpeed);
void stopMotors();
void rotateLeft(int speed);
void rotateRight(int speed);

float getPWMvalue(int speed);

Stability adjustPWMvalueByPulse(float *leftPWMValue, float *rightPWMValue);

