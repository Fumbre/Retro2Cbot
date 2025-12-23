#pragma once
#include "common/robot/motor/motor.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/sonar/sonar.h"
#include "common/tools/Start_sequence.h"

void mazeLineSetup();

void mazeLine();

int getPWMValue(int speed);