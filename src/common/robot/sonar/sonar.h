#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/robot/movement/movement.h"

void setupSonar();
float getDistanceCM();
bool isObstacleDetected(float limit_cm);
void avoidObstacleSmoothNonBlocking(int speed);

extern bool avoiding;
