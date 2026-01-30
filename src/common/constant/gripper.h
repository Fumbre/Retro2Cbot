/**
 * @name constant of Gripper
 * @author Francisco
 * @date 25-10-2025
*/

#pragma once
#include "common/constant/board.h"

#if defined(BB016) || defined(BB046)
const int GRIPPER = 12;
#endif

#ifdef BB011
const int GRIPPER = 4;
#endif