/**
 * @name interface of gripper
 * @author Francisco
 * @date 03-12-2025
 */
#pragma once
#include <Arduino.h>
#include "common/constant/gripper.h"
#include "common/robot/globalvariable/globalVariable.h"

void setupGripper();
void gripper(int pulseMicroseconds);
void gripperCatch();
void gripperUnCatch();
