#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/constant/board.h"

void setupSonar();
float getDistanceCM_Front();
bool isObstacleFront(float limit_cm);

bool isObstacleRight(float limit_cm);
bool isObstacleLeft(float limit_cm);

float getDistanceCM_Left();
float getDistanceCM_Right();
