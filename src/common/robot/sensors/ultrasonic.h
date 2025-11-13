#pragma once
#include <Arduino.h>

void initUltrasonic();
float getDistanceCM();
bool isObstacleDetected(float threshold_cm = 30.0);
