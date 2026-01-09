#pragma once
#include "board.h"

#if defined(BB016) || defined(BB046)

const int PIN_SONAR_TRIG = 7;
const int PIN_SONAR_ECHO_FRONT = 8;

#endif

#ifdef BB011

const int PIN_SONAR_TRIG = 12; // Shared Trigger
const int PIN_SONAR_ECHO_FRONT = 8;
const int PIN_SONAR_ECHO_RIGHT = 7;
const int PIN_SONAR_ECHO_LEFT = 5;

#endif