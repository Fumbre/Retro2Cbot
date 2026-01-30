/**
 * @name interface of Sonar
 * @author Francisco & Uraib
 * @date 11-12-2025
*/

#pragma once
#include <Arduino.h>
#include "common/constant/sonar.h"
#include "common/constant/board.h"
#include "common/robot/globalvariable/globalVariable.h"

void setupSonar();

float getDistanceCM_Front();
float getDistanceCM_Left();
float getDistanceCM_Right();

bool isObstacleFront(float limit_cm);
bool isObstacleRight(float limit_cm);
bool isObstacleLeft(float limit_cm);
