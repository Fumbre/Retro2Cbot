#pragma once
#include <Arduino.h>
#include "common/constant/ultrasonic.h"

void setupUltrasonicSensor();
float getDistanceCM();
bool isObstacleDetected(float limit_cm = 30.0);