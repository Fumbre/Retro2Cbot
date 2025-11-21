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

// // // PID factors
// const float Kp_f = 4.5; // Proportional
// const float Ki_f = 2.9; // Integral
// const float Kd_f = 0.2;  // Derivative

// const float Kp_b = 5.0;
// const float Ki_b = 2.2;
// const float Kd_b = 0.12;

// const float MOTOR_LEFT_FACTOR = 1.0;
// const float MOTOR_RIGHT_FACTOR = 0.95;

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

// PID factors
const float Kp_f = 4.0;  // Proportional
const float Ki_f = 1.9;  // Integral
const float Kd_f = 0.12; // Derivative

const float Kp_b = 5.9;
const float Ki_b = 2.2;
const float Kd_b = 0.12;

const float MOTOR_LEFT_FACTOR = 0.985;
const float MOTOR_RIGHT_FACTOR = 1.0;

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