/**
 * @name interface of following line
 * @author Fumbre (Vladyslav)
 * @date 15-12-2025
 */
#pragma once
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/actions/obstacle_avoidance.h"
#include "common/robot/gripper/gripper.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/actions/Sequence.h"
#include "common/robot/datasend/datasend.h"

void followLine();
void followLineSetup();
void solvingFollowSingleLine(LineState currnetPattern, int fullSpeed, float slightConf, float hardConf);
