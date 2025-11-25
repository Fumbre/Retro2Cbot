#pragma once
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/robot/motor/motor.h"
#include "common/constant/robot.h"

void moveForward(int speed);

void moveBackward(int speed);

void switchDirection(int leftSpeed, int rightSpeed);

void stopMotors();

float getPWMvalue(int speed);

void rotate(int speed, String direction, float angle);

void adjustPWMvalueByPulse(float &leftPWMValue, float &rightPWMValue);

void rotateLeft(int speed);
void rotateRight(int speed);