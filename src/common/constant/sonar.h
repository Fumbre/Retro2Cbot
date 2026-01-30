/**
 * @name constant of Sonar
 * @author Francisco & Uraib
 * @date 11-12-2025
*/

#pragma once
#include "board.h"

#if defined(BB016) || defined(BB046)

const int PIN_SONAR_TRIG = 7;
const int PIN_SONAR_ECHO_FRONT = 8;

#endif

#ifdef BB011

const int PIN_SONAR_TRIG = 12;              // Shared Trigger
const int PIN_SONAR_ECHO_FRONT = 8;         // front sonar echo pin
const int PIN_SONAR_ECHO_RIGHT = 7;         // fleft sonar echo pin
const int PIN_SONAR_ECHO_LEFT = 5;          // right sonar echo pin

#endif