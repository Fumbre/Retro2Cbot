/**
 * @name interface of motor
 * @author Fumbre (Vladyslav)
 * @date 13-11-2025
 */
#pragma once
#include "common/constant/board.h"
#include <Arduino.h>
#include "common/constant/motor.h"
#include "common/tools/Timer.h"
#include "common/robot/globalvariable/globalVariable.h"

void setupMotor();

void setupMotor();
void countLeftPulses();
void countRightPulses();
void setupPulseCounter();

struct Stability
{
  int speedLeft;
  int speedRight;
};
