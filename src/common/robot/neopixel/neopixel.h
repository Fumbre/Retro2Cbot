/**
 * @name interface of Neopixel
 * @author Sunny
 * @date 24-11-2025
 */

#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "common/constant/neopixel.h"

void initNeopixel();
RGB checkRGBvalue(int &R, int &G, int &B);
void turnONAllNeoPixels(int R, int G, int B);
void turnOffAllNeopixel();
void turnOnSomeNeopixels(int index[],int length, int R, int G, int B);
void turnOffSomeNeopixels(int index[], int length);
