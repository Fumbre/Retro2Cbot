/**
 * @name constants for robot
 * @authors Sunny
 * @date 10-11-2025
 */

#pragma once
#include "board.h"

// the distance between robot center and wheels center unit:cm
const float ROBOT_RADUIS = 6.5;

// the raduis of per wheel unit: cm
const float WHEEL_RADUIS = 3.6;

// what map this robot for
#ifdef BB046
const int SETTING_MODE = 1;
#endif

#ifdef BB016
const int SETTING_MODE = 2;
#endif

#ifdef BB011
const int SETTING_MODE = 3;
#endif