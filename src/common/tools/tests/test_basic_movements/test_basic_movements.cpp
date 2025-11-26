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
  if (timestampTestBasicMovementForward.executeOnce(0, 3000))
  {
    moveSpeed(240, 240);
  }

  if (timestampTestBasicMovementBackward.executeOnce(1000 + 2000, 3000))
  {
    moveSpeed(-240, -240);
  }

  if (timestampTestBasicMovementForward1.executeOnce(2000 + 4000, 500))
  {
    moveSpeed(240, 240);
  }

  if (timestampTestBasicMovementRight.executeOnce(2500 + 4000, 1000))
  {
    switchDirection(240, 130);
  }

  if (timestampTestBasicMovementRight1.executeOnce(3500 + 4000, 200))
  {
    switchDirection(240, 140);
  }

  if (timestampTestBasicMovementLeft.executeOnce(3700 + 4000, 300))
  {
    switchDirection(140, 240);
  }

  if (timestampTestBasicMovementLeft1.executeOnce(4000 + 4000, 1500))
  {
    moveSpeed(200, 200);
  }

  if (timestampTestBasicMovementForward2.executeOnce(5500 + 4000, 2000))
  {
    moveSpeed(240, 240);
  }

  if (timestampTestBasicMovementRotateLeft.executeOnce(7500 + 4000, 1000))
  {
    moveSpeed(240, -240);
  }

  if (timestampTestBasicMovementStopMotors.executeOnce(8500 + 4000))
  {
    stopMotors();
  }
}