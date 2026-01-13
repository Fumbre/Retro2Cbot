#pragma once
#include "common/robot/motor/motor.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/Timer.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/hc12/hc12.h"
#include <ArduinoJson.h>
#include "common/robot/actions/Sequence.h"
#include "common/robot/neopixel/neopixel.h"
#include "common/robot/datasend/datasend.h"

void mazeLineSetup();

void mazeLine();

void rotate(int dir);