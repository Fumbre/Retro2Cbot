#pragma once
#include "common/robot/globalvariable/globalVariable.h"
#include "common/tools/Timer.h"
#include <Arduino.h>
#include "common/constant/board.h"
#include "common/robot/hc12/hc12.h"

void dataSend();
void sendSonarData();
void sendGripperData();
void sendReflectiveSensorData();
void sendNeopixelData();
String getCurrentRobotCode();