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
    moveStabilized(240, 240);
    // moveForward(100);
  }

  if (timestampTestBasicMovementBackward.executeOnce(1000 + 2000, 3000))
  {
    moveStabilized(-240, -240);
    // moveBackward(100);
  }

  if (timestampTestBasicMovementForward1.executeOnce(2000 + 4000, 500))
  {
    moveStabilized(240, 240);
    // moveForward(100);
  }

  if (timestampTestBasicMovementRight.executeOnce(2500 + 4000))
  {
    writeSpeed(240, 120);
  }

  if (timestampTestBasicMovementRight1.executeOnce(3500 + 4000))
  {
    writeSpeed(240, 130);
  }

  if (timestampTestBasicMovementLeft.executeOnce(3700 + 4000))
  {
    writeSpeed(120, 240);
  }

  if (timestampTestBasicMovementLeft1.executeOnce(4000 + 4000))
  {
    writeSpeed(125, 240);
  }

  if (timestampTestBasicMovementForward2.executeOnce(5500 + 4000, 2000))
  {
    moveStabilized(240, 240);
    // moveForward(100);
  }

  if (timestampTestBasicMovementRotateLeft.timeout(7500 + 4000))
  {
    // moveStabilized(240, -240);

    // moveForward(100);

    if (didMoveLeft(255, 22))
    {
      moveStopAll();
    }
  }
}