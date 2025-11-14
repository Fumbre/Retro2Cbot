#pragma once
#include <Arduino.h>
#include "common/constant/motor.h"

void setupMotor();

volatile long motor_left_pulses_counter = 0;
volatile long motor_right_pulses_counter = 0;

void countLeftPulses();
void countRightPulses();