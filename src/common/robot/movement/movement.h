#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

void moveForward(int speed, bool isPure);
void moveBackward(int speed);
void moveRight(int speed);
void moveLeft(int speed);

void rotateLeft(int speed, bool isPure);
void rotateRight(int speed);

void moveStop(int wheel_pin);