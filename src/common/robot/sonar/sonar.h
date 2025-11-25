#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/robot/movement/movement.h"

void setupSonar();
float getDistanceCM();
void avoidObstacleSmoothNonBlocking(int speed);

extern bool avoiding;
