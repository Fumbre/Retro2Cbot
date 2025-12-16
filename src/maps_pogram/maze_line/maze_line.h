#pragma once
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/movement/movement.h"

void mazeLineSetup();

void mazeLine(int speed);

int getPWMValue(int speed);