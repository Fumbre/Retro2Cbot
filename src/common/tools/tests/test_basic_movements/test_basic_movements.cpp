#include "test_basic_movements.h"

Timer timestampTestBasicMovementForward;
Timer timestampTestBasicMovementForward1;
Timer timestampTestBasicMovementForward2;

Timer timestampTestBasicMovementBackward;

Timer timestampTestBasicMovementRight;
Timer timestampTestBasicMovementRight1;

Timer timestampTestBasicMovementLeft;
Timer timestampTestBasicMovementLeft1;

Timer timestampTestBasicMovementRotateLeft;

Timer timestampTestBasicMovementStopMotors;

/**
 * @name testBasicMovement
 * @author Fumbre (Vladyslav)
 * @date 21-11-2025
 * @details make test for basic movements
 */
void testBasicMovement()
{
  if (timestampTestBasicMovementForward.executeOnce(0))
  {
    moveForward(100);
  }

  if (timestampTestBasicMovementBackward.executeOnce(1000 + 2000))
  {
    moveBackward(100);
  }

  if (timestampTestBasicMovementForward1.executeOnce(2000 + 4000))
  {
    moveForward(100);
  }

  if (timestampTestBasicMovementRight.executeOnce(2500 + 4000))
  {
    switchDirection(100, 40);
  }

  if (timestampTestBasicMovementRight1.executeOnce(3500 + 4000))
  {
    switchDirection(100, 50);
  }

  if (timestampTestBasicMovementLeft.executeOnce(3700 + 4000))
  {
    switchDirection(40, 100);
  }

  if (timestampTestBasicMovementLeft1.executeOnce(4000 + 4000))
  {
    switchDirection(50, 100);
  }

  if (timestampTestBasicMovementForward2.executeOnce(5500 + 4000))
  {
    moveForward(100);
  }

  if (timestampTestBasicMovementRotateLeft.executeOnce(7500 + 4000))
  {
    rotateLeft(255);
  }

  if (timestampTestBasicMovementStopMotors.executeOnce(8600 + 4000))
  {
    stopMotors();
  }
}