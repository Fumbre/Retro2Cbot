#pragma once
#include <Arduino.h>
#include "common/constant/motor.h"

void setupMotor();

extern volatile long motor_left_pulses_counter;
extern volatile long motor_right_pulses_counter;

void countLeftPulses();
void countRightPulses();

// motorStability();