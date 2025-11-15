#pragma once
#include <Arduino.h>
#include "common/tools/timer.h"

void initializeUltrasonicSensor();
float getDistanceCM();
bool isObstacleDetected(float limit_cm = 30.0);
void avoidObstacle();