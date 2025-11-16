#include "common/robot/motor/motor.h"
#include "common/robot/movement/movement.h"
#include "common/tools/tests/test_pulses.h"
#include "common/tools/timer.h"
#include <Arduino.h>

const int SETTING_MODE = 2;

Timer doCoolRotation;
Timer test;

void setup() {
  Serial.begin(9600);
  setupMotor();
}

Timer stampForward;
Timer stampBackward;
Timer stampRotateLeft;
Timer stampRotateRight;

int pass = false;

void loop() {

  testPulses(1000);

  //------------first test------------------
  // if (stampForward.every(1000, 1500))
  // {
  //   moveBackward(255);
  // }
  // else
  // {
  //   moveForward(255);
  // }

  //------------second test------------------
  //  if (stampForward.timeout(3000))
  //   {
  //     stampForward.hardReset();
  //     stampBackward.hardReset();
  //     stampRotateLeft.hardReset();
  //   }

  //   if (stampForward.once(0))
  //   {
  //     moveForward(255);
  //   }

  //   if (stampBackward.once(1000))
  //   {
  //     moveBackward(255);
  //   }

  //   if (stampRotateLeft.once(2000))
  //   {
  //     rotateLeft(255);
  //   }

  //------------three test------------------

  if (!doCoolRotation.timeout(32000)) {
    if (test.every(22)) {
      if (stampRotateLeft.every(20, 20)) {
        rotateLeft(255);
      } else {
        rotateRight(255);
      }
      moveForward(255);
    }
  }

  if (doCoolRotation.once(32000)) {
    moveStopAll();
  }

  switch (SETTING_MODE) {
  case 0:
    // to do followSingleLine
    break;
  case 1:
    // to do mazeLine
    break;
  case 2:
    // to do physicalMaze
    break;

  default:
    Serial.print("NO SUCH A PROGRAM");
    break;
  }
}
