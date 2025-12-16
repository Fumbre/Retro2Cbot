#pragma once
#include <Arduino.h>

// RS - reflective sensor
// D* is board naming
const int PIN_RS_D8 = A0; // D8
const int PIN_RS_D7 = A1;
const int PIN_RS_D6 = A2;
const int PIN_RS_D5 = A3;
const int PIN_RS_D4 = A4;
const int PIN_RS_D3 = A5;
const int PIN_RS_D2 = A6;
const int PIN_RS_D1 = A7;

// difference between initial surface and next read
// example: first value is 255 after 255 + THRESHOLD next surface value
const int THRESHOLD = 275;

// Second rs data margin of error
const int MARGIN_SURFACE = 100;

const int PINS_RS[] = {
    PIN_RS_D8,
    PIN_RS_D7,
    PIN_RS_D6,
    PIN_RS_D5,
    PIN_RS_D4,
    PIN_RS_D3,
    PIN_RS_D2,
    PIN_RS_D1,
};

const int PINS_RS_LENGTH = sizeof(PINS_RS) / sizeof(int);
// to store array length dynamically
