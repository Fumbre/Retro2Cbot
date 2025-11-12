#pragma once

// ======================BB0011======================

// const int WHEEL_RIGHT_FORWARD_PIN = 11;
// const int WHEEL_RIGHT_BACKWARD_PIN = 10;

// const int WHEEL_LEFT_FORWARD_PIN = 9;
// const int WHEEL_LEFT_BACKWARD_PIN = 6;

// const int WHEEL_LEFT_ROTATION_PIN = 5;
// const int WHEEL_RIGHT_ROTATION_PIN = 3;

// ==================================================

// ======================BB0046======================

const int WHEEL_RIGHT_FORWARD_PIN = 9;
const int WHEEL_RIGHT_BACKWARD_PIN = 6;

const int WHEEL_LEFT_FORWARD_PIN = 10;
const int WHEEL_LEFT_BACKWARD_PIN = 11;

const int WHEEL_LEFT_ROTATION_PIN = 5;
const int WHEEL_RIGHT_ROTATION_PIN = 3;

// ==================================================

struct Robot
{
  String title;
  int PIN;
};

const int WHEEL_ARRAY_LENGTH = 6;

const Robot WHEEL_ARRAY[WHEEL_ARRAY_LENGTH] = {
    {
        "WHEEL_RIGHT_FORWARD_PIN",
        WHEEL_RIGHT_FORWARD_PIN,
    },
    {
        "WHEEL_RIGHT_BACKWARD_PIN",
        WHEEL_RIGHT_BACKWARD_PIN,
    },
    {
        "WHEEL_LEFT_FORWARD_PIN",
        WHEEL_LEFT_FORWARD_PIN,
    },
    {
        "WHEEL_LEFT_BACKWARD_PIN",
        WHEEL_LEFT_BACKWARD_PIN,
    },
    {
        "WHEEL_LEFT_ROTATION_PIN",
        WHEEL_LEFT_ROTATION_PIN,
    },
    {
        "WHEEL_RIGHT_ROTATION_PIN",
        WHEEL_RIGHT_ROTATION_PIN,
    },
};
