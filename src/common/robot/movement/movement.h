#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

void moveForward(bool isPure);
void moveBackward(bool isPure);
void moveRight(bool isPure);
void moveLeft(bool isPure);

void rotateLeft(bool isPure);
void rotateRight(bool isPure);

void moveStop();