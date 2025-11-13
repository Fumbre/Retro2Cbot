#pragma once
#include <Arduino.h>

void initUltrasonic();
float getDistanceCM();
bool isObstacleDetected(float limit_cm = 30.0);
