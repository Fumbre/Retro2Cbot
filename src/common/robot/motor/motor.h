#pragma once
#include <Arduino.h>
#include "common/tools/timer.h"

void setupMotor();

extern volatile long motor_left_pulses_counter;
extern volatile long motor_right_pulses_counter;

void countLeftPulses();
void countRightPulses();

struct Stability {
    int speedLeft;
    int speedRight;
};

Stability motorStability(int speed);