#pragma once
#include <Arduino.h>
#include "common/constant/motor.h"

void moveForward(int speed);
void moveBackward(int speed);
void moveRight(int speed);
void moveLeft(int speed);

void rotateLeft(int speed);

void moveStop(int wheel_pin);