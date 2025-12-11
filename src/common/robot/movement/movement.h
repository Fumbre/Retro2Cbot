#pragma once
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/constant/motor.h"
#include "common/robot/motor/motor.h"
#include "common/tools/Timer.h"

void resetMoveRight();
void resetMoveLeft();
bool didMoveRight(int speed, int pulses);
bool didMoveLeft(int speed, int pulses);

void moveStop(int motor_pin);
void moveStopAll();

void moveSpeed(int speedLeft, int speedRight);
void moveStabilized(int speedLeft, int speedRight);

void writeSpeed(int speedLeft, int speedRight);

extern Timer didMoveRightTimer;
extern Timer didMoveLeftTimer;   

