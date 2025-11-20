#include "test_basicMovements.h"

Timer stampTestForward;
Timer stampTestForward1;
Timer stampTestForward2;
Timer stampTestForward3;

Timer stampTestBackward;

Timer stampTestMoveLeft;
Timer stampTestMoveLeft1;
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

  if (stampTestBackward.executeOnce(1000))
  {
    moveBackward(100);
  }

  if (stampTestForward1.executeOnce(2000))
  {
    moveForward(100);
  }
  if (stampTestMoveRight.executeOnce(2500))
  {
    switchDirection(100, 40);
  }
  if (stampTestForward1.executeOnce(3000))
  {
    switchDirection(80, 100);
  }

  if (stampTestRotateLeft.executeOnce(3500))
  {
    switchDirection(30, 100);
    // moveForward(100);
    // switchDirection(100, 100);
    // switchDirection(50, 100);
  }

  if (stampTestForward2.executeOnce(4600))
  {
    moveForward(100);
  }

  if (stampTestMoveLeft1.executeOnce(5000))
  {
    switchDirection(30, 100);
  }

  if (stampTestForward3.executeOnce(5500))
  {
    switchDirection(40, 100);
  }

  if (stampTestMoveRight1.executeOnce(6000))
  {
    switchDirection(100, 30);
  }

  if (stampTestMoveRight2.executeOnce(6900))
  {
    stopMotors();
    // moveForward(100);
  }

  if (stampTestStop.executeOnce(7000))
  {
    stopMotors();
    // 80 20
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

  if (stampTestRotateLeft1.executeOnce(61000))
  {
    rotateLeft(255);
  }
  if (stampTestStop.executeOnce(69100))
  {
    stopMotors();
  }
}