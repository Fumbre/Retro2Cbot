#pragma once

const int FULL_PWM_VALUE = 255;
const int FULL_SPEED = 100;                         // in precentage

// 20 pulses per wheel rotation
const int PULSES_PER_ROTATION = 20;

// ======================BB016======================

#ifdef BB016

const int PIN_MOTOR_RIGHT_FORWARD = 10;
const int PIN_MOTOR_RIGHT_BACKWARD = 6;

const int PIN_MOTOR_LEFT_FORWARD = 5;
const int PIN_MOTOR_LEFT_BACKWARD = 9;

const int PIN_MOTOR_LEFT_PULSE = 2;
const int PIN_MOTOR_RIGHT_PULSE = 3;

// PID factors
const float Kp_front = 4.5;                 // Proportional
const float Ki_front = 2.9;                 // Integral
const float Kd_front = 0.2;                 // Derivative

const float Kp_back = 5.0;
const float Ki_back = 2.2;
const float Kd_back = 0.12;

#endif

// ==================================================

// ======================BB011======================

#ifdef BB011

const int PIN_MOTOR_RIGHT_FORWARD = 11;
const int PIN_MOTOR_RIGHT_BACKWARD = 10;

const int PIN_MOTOR_LEFT_FORWARD = 9;
const int PIN_MOTOR_LEFT_BACKWARD = 6;

const int PIN_MOTOR_LEFT_PULSE = 2;
const int PIN_MOTOR_RIGHT_PULSE = 3;

// PID factors
const float Kp_front = 4.5; // Proportional
const float Ki_front = 2.9; // Integral
const float Kd_front = 0.2; // Derivative

const float Kp_back = 5.0;
const float Ki_back = 2.2;
const float Kd_back = 0.12;

#endif

// ==================================================

// ======================BB046======================

#ifdef BB046

const int PIN_MOTOR_RIGHT_FORWARD = 9;
const int PIN_MOTOR_RIGHT_BACKWARD = 6;

const int PIN_MOTOR_LEFT_FORWARD = 10;
const int PIN_MOTOR_LEFT_BACKWARD = 11;

const int PIN_MOTOR_LEFT_PULSE = 3;  // shoud be 3 !
const int PIN_MOTOR_RIGHT_PULSE = 2; // shoud be 2 !

// PID factors
const float Kp_front = 4.0;  // Proportional
const float Ki_front = 1.9;  // Integral
const float Kd_front = 0.12; // Derivative

const float Kp_back = 5.9;
const float Ki_back = 2.2;
const float Kd_back = 0.12;

#endif

// ==================================================

#if defined(BB046) || defined(BB011) || defined(BB016)

//  PINS MOTOR ARRAY
const int PINS_MOTOR[] = {
    PIN_MOTOR_RIGHT_FORWARD,
    PIN_MOTOR_RIGHT_BACKWARD,
    PIN_MOTOR_LEFT_FORWARD,
    PIN_MOTOR_LEFT_BACKWARD,
};

//  PINS MOTOR ARRAY LENGTH
// To store array length dynamically
const int PINS_MOTOR_LENGTH = sizeof(PINS_MOTOR) / sizeof(int);

#endif
