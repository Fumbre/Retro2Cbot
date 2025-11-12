/**
 * @name constants for robot
 * @authors Sunny & Nicolo
 * @date 10-11-2025
 */

#pragma once

// =========================BB016==============================

// the pin of directions of wheels BB016
const int LEFT_DIRECTION_FORWARD_PIN = 5;
const int LEFT_DIRECTION_BACKWARD_PIN = 9;
const int RIGHT_DIRECTION_FORWARD_PIN = 10;
const int RIGHT_DIRECTION_BACKWARD_PIN = 6;

// pin for rotation
const int LEFT_ROTATION_PIN = 3;
const int RIGHT_ROTATION_PIN = 2;

const int FULL_PWM_VALUE = 255;
const int FULL_SPEED = 100; // in precentage
// the distance between robot center and wheels center unit:cm
const float ROBOT_RADUIS = 9.53;
// the 20 pulses in per rotation of wheel
const int PPR = 15;
// the raduis of per wheel unit: cm
const float WHEEL_RADUIS = 3.6;

const float MOTOR_LEFT_FACTOR = 1.00;          // stablize left motor
const float MOTOR_RIGHT_FACTOR = 0.9764705882; // stablize right motor 249÷255=0.976470588...

const int WHEEL_PIN_ARRAY[] = {
    LEFT_DIRECTION_FORWARD_PIN,
    LEFT_DIRECTION_BACKWARD_PIN,
    RIGHT_DIRECTION_FORWARD_PIN,
    RIGHT_DIRECTION_BACKWARD_PIN};

// =========================BB011==============================

// Robot BB011
// const int LEFT_DIRECTION_FORWARD_PIN = 8;
// const int LEFT_DIRECTION_BACKWARD_PIN = 7;
// const int RIGHT_DIRECTIONL_FORWARD_PIN = 2;
// const int RIGHT_DIRECTIONL_BACKWARD_PIN = 4;

// // pin of speed of wheels
// const int LEFT_SPEED_PIN = 3;
// const int RIGHT_SPEED_PIN = 9;

// // pin of steering gear
// const int STEERING_GEAR_PIN = 10;

// =========================BB007==============================

// Robot BB007
//  const int LEFT_DIRECTION_FORWARD_PIN = 8;
//  const int LEFT_DIRECTION_BACKWARD_PIN = 7;
//  const int RIGHT_DIRECTIONL_FORWARD_PIN = 2;
//  const int RIGHT_DIRECTIONL_BACKWARD_PIN = 4;

// // pin of speed of wheels
// const int LEFT_SPEED_PIN = 3;
// const int RIGHT_SPEED_PIN = 9;

// // pin of steering gear
// const int STEERING_GEAR_PIN = 10;
