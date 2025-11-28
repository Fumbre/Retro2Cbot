/**
 * @name interface of Neopixel
 * @author Sunny
 * @date 24-11-2025
 */

#pragma once
#include "common/constant/neopixel.h"
#include "common/tools/Neopixel.h"

void initNeopixelPins();

void turnOnAllLeds(int R, int G, int B);

void turnOffAllLeds();

void turnOnSomeLeds(int index[], int length, int R, int G, int B);

void turnOffSomeLeds(int index[], int length);