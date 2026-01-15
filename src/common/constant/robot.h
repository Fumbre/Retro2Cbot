/**
 * @name constants for robot
 * @authors Sunny
 * @date 10-11-2025
*/

#pragma once
#include "board.h"

// distance between robot center and wheels center (cm)
const float ROBOT_RADUIS = 6.5;

// radius per wheel (cm)
const float WHEEL_RADUIS = 3.6;

// what map this robot for

// Follow Line
#ifdef BB046
const int SETTING_MODE = 1;
#endif

// Maze Line
#ifdef BB016
const int SETTING_MODE = 2;
#endif

// Physical Maze
#ifdef BB011
const int SETTING_MODE = 3;
#endif
