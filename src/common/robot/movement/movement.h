#pragma once
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/constant/motor.h"
#include "common/robot/motor/motor.h"

void moveRight(int speed);
void moveLeft(int speed);

void moveStop(int wheel_pin);
void stopMotors();

void switchDirection(int speedLeft, int speedRight);

void moveSpeed(int speedLeft, int speedRight);
void moveStabilized(int speedLeft, int speedRight);