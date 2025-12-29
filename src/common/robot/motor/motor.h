#pragma once
#include "common/constant/board.h"
#include <Arduino.h>
#include "common/constant/motor.h"
#include "common/tools/Timer.h"

extern volatile long motor_left_pulses_counter;
extern volatile long motor_right_pulses_counter;

void setupMotor();
void countLeftPulses();
void countRightPulses();
void setupPulseCounter();

struct Stability {
  int speedLeft;
  int speedRight;
};
