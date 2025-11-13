#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

void moveForward(int speed);

void moveBackward(int speed);

void switchDirection(int leftSpeed, int rightSpeed);

void stopMotors();

int getPWMvalue(int speed);

void initWheelsPin();

void rotate180(int speed, String direction);

void StartSpeedControl();

void MoveFrontControlled(int speedBase);