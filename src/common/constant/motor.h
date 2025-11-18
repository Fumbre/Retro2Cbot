#pragma once

const int FULL_PWM_VALUE = 255;
const int FULL_SPEED = 100; // in precentage

// the 20 pulses in per rotation of wheel
const int PPR = 20;

// ======================BB016======================

// const int PIN_MOTOR_RIGHT_FORWARD = 10;
// const int PIN_MOTOR_RIGHT_BACKWARD = 6;

// const int PIN_MOTOR_LEFT_FORWARD = 5;
// const int PIN_MOTOR_LEFT_BACKWARD = 9;

// const int PIN_MOTOR_LEFT_PULSE = 2;
// const int PIN_MOTOR_RIGHT_PULSE = 3;

// ==================================================

// ======================BB011======================

// const int PIN_MOTOR_RIGHT_FORWARD = 9;
// const int PIN_MOTOR_RIGHT_BACKWARD = 6;

// const int PIN_MOTOR_LEFT_FORWARD = 11;
// const int PIN_MOTOR_LEFT_BACKWARD = 10;

// const int PIN_MOTOR_LEFT_PULSE = 2;
// const int PIN_MOTOR_RIGHT_PULSE = 3;

// ==================================================

// ======================BB0046======================

const int PIN_MOTOR_RIGHT_FORWARD = 9;
const int PIN_MOTOR_RIGHT_BACKWARD = 6;

const int PIN_MOTOR_LEFT_FORWARD = 10;
const int PIN_MOTOR_LEFT_BACKWARD = 11;

const int PIN_MOTOR_LEFT_PULSE = 2;
const int PIN_MOTOR_RIGHT_PULSE = 3;

// ==================================================

// DISCUSS PIN_MOTOR_ARRAY and PIN_MOTOR_ARRAY_LENGTH
const int PINS_MOTOR[] = {
    PIN_MOTOR_RIGHT_FORWARD,
    PIN_MOTOR_RIGHT_BACKWARD,
    PIN_MOTOR_LEFT_FORWARD,
    PIN_MOTOR_LEFT_BACKWARD,
};

// ----discuss----
// const int PINS_MOTOR_PULSE[] = {
//     PIN_MOTOR_LEFT_PULSE,
//     PIN_MOTOR_RIGHT_PULSE,
// };

// const int PINS_MOTOR_PULSE_LENGTH = sizeof(PINS_MOTOR_PULSE) / sizeof(int);
// ----------------------------

const int PINS_MOTOR_LENGTH = sizeof(PINS_MOTOR) / sizeof(int);