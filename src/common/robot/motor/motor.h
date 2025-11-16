#pragma once
#include <Arduino.h>
#include "common/tools/timer.h"

void setupMotor();

extern volatile long motor_left_pulses_counter;
extern volatile long motor_right_pulses_counter;

extern struct MotorSpeed correctSpeed;

void countLeftPulses();
void countRightPulses();

struct MotorSpeed
{
  int speedLeft;
  int speedRight;
};

MotorSpeed motorStability(int speed);