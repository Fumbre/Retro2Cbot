#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/robot/movement/movement.h"
#include "common/robot/movement/movementPID.h"
#include "common/constant/board.h"

void setupSonar();
float getDistanceCM_Front();
// float getDistanceCM_Right();
// float getDistanceCM_Left();

bool isObstacleFront(float limit_cm);
// bool isObstacleRight(float limit_cm);
// bool isObstacleLeft(float limit_cm);

void avoidObstacleSmoothNonBlocking(int speed);

extern bool avoiding;
