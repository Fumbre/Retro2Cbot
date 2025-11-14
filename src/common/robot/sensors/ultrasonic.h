#pragma once
#include <Arduino.h>

void initializeUltrasonicSensor();
float getDistanceCM();
bool isObstacleDetected(float limit_cm = 30.0);
