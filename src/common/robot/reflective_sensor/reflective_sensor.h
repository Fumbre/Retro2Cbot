#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"

void initReflectiveSensorPins();

WheelSpeed checkLine(int baseSpeed);
