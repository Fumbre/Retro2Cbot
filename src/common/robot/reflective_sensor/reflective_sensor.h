#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"
#include "common/tools/Welford.h"
#include "common/robot/movement/movementPID.h"

void initReflectiveSensorPins();

WheelSpeed checkLine(int baseSpeed);
