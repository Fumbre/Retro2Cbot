#include "test_basicMovements.h"

Timer stampTestForward;
Timer stampTestForward1;
Timer stampTestForward2;
Timer stampTestForward3;

Timer stampTestBackward;

Timer stampTestMoveLeft;
Timer stampTestMoveLeft1;
Timer stampTestMoveLeft2;
Timer stampTestMoveRight;
Timer stampTestMoveRight1;
Timer stampTestMoveRight2;

Timer stampTestRotateLeft;
Timer stampTestRotateLeft1;

Timer stampTestRotateRight;
Timer stampTestRotateRight1;
Timer stampTestRotateRight2;

Timer stampTestStop;

void testBasicMovement()
{
  if (stampTestForward.executeOnce(0))
  {
    moveForward(100);
  }

  if (stampTestBackward.executeOnce(1000 + 2000))
  {
    moveBackward(100);
  }

  if (stampTestForward1.executeOnce(2000 + 4000))
  {
    moveForward(100);
  }
  if (stampTestMoveRight.executeOnce(2500 + 4000))
  {
    switchDirection(100, 40);
  }
  if (stampTestForward1.executeOnce(3500 + 4000))
  {
    switchDirection(100, 50);
  }

  if (stampTestRotateLeft.executeOnce(3700 + 4000))
  {
    switchDirection(40, 100);
  }

  if (stampTestForward2.executeOnce(4000 + 4000))
  {
    // moveForward(100);
    switchDirection(50, 100);
  }

  if (stampTestMoveLeft1.executeOnce(5500 + 4000))
  {
    moveForward(100);
  }

  //
  if (stampTestMoveLeft2.executeOnce(7500 + 4000))
  {
    rotateLeft(255);
  }
  if (stampTestStop.executeOnce(8600 + 4000))
  {
    stopMotors();
  }

  // if (stampTestMoveLeft1.executeOnce(5000))
  // {
  //   switchDirection(100, 20);
  // }

  // if (stampTestMoveLeft1.executeOnce(5500))
  // {
  //   moveForward(100);
  // }

  // if (stampTestRotateRight1.executeOnce(5500))
  // {
  //   switchDirection(100, 60);
  // }
  // if (stampTestRotateRight2.executeOnce(6500))
  // {
  //   moveForward(100);
  // }
}