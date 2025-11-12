#pragma once

// ======================BB0011======================

// const int MOTOR_RIGHT_FORWARD_PIN = 11;
// const int MOTOR_RIGHT_BACKWARD_PIN = 10;

// const int MOTOR_LEFT_FORWARD_PIN = 9;
// const int MOTOR_LEFT_BACKWARD_PIN = 6;

// const int MOTOR_LEFT_PULSE_PIN = 5;
// const int MOTOR_RIGHT_PULSE_PIN = 3;

// ==================================================

// ======================BB0046======================

const int MOTOR_RIGHT_FORWARD_PIN = 9;
const int MOTOR_RIGHT_BACKWARD_PIN = 6;

const int MOTOR_LEFT_FORWARD_PIN = 10;
const int MOTOR_LEFT_BACKWARD_PIN = 11;

const int MOTOR_LEFT_PULSE_PIN = 5;
const int MOTOR_RIGHT_PULSE_PIN = 3;

// ==================================================

struct Robot
{
  String title;
  int PIN;
};

const int MOTOR_ARRAY_LENGTH = 6;

const Robot MOTOR_ARRAY[MOTOR_ARRAY_LENGTH] = {
    {
        "MOTOR_RIGHT_FORWARD_PIN",
        MOTOR_RIGHT_FORWARD_PIN,
    },
    {
        "MOTOR_RIGHT_BACKWARD_PIN",
        MOTOR_RIGHT_BACKWARD_PIN,
    },
    {
        "MOTOR_LEFT_FORWARD_PIN",
        MOTOR_LEFT_FORWARD_PIN,
    },
    {
        "MOTOR_LEFT_BACKWARD_PIN",
        MOTOR_LEFT_BACKWARD_PIN,
    },
    {
        "MOTOR_LEFT_PULSE_PIN",
        MOTOR_LEFT_PULSE_PIN,
    },
    {
        "MOTOR_RIGHT_PULSE_PIN",
        MOTOR_RIGHT_PULSE_PIN,
    },
};
