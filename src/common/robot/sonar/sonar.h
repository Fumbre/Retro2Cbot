#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/robot/movement/movementPID.h"

void setupSonar();
float getDistanceCM_Front();
float getDistanceCM_Right();

bool isObstacleFront(float limit_cm);
bool isObstacleRight(float limit_cm);