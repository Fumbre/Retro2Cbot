#include "test_basicMovements.h"

Timer stampTestObstacleRotateRight;
Timer stampTestObstacleRotateRight1;

Timer stampTestObstacleRotateLeft;

Timer stampTestObstacleForward;
Timer stampTestObstacleForward1;

void testObstacle()
{
  if (stampTestObstacleRotateRight.executeOnce(0))
  {
    rotateRight(255);
  }

  if (stampTestObstacleForward.executeOnce(700))
  {
    moveForward(100);
  }
  if (stampTestObstacleRotateRight.executeOnce(1400))
  {
    rotateLeft(255);
  }

  if (stampTestObstacleRotateRight1.executeOnce(1500))
  {
    rotateRight(255);
  }

  if (stampTestObstacleForward1.executeOnce(2000))
  {
    moveForward(100);
  }
}