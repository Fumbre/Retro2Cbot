#pragma once
#include "Arduino.h"
#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"
#include "common/tools/Timer.h"
#include "common/robot/actions/Sequence.h"

#include "common/robot/actions/Sequence.h"

void physicalMaze();

void physicalMazeSetup();

void solvingPhysicalMaze();