#pragma once

#include "common/constant/reflective_sensor.h"
#include "common/tools/reflective_sensor/Line_Follower.h"
#include "common/tools/reflective_sensor/Line_Interrupter.h"
#include "common/tools/reflective_sensor/Line_sensor.h"

void initReflectiveSensor();

FollowerResult lineFollow();
