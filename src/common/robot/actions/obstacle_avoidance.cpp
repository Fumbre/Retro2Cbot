#include "obstacle_avoidance.h"

bool avoiding = false;

/*
 * @name obstacleAvoidance
 * @author Francisco
 * @date 20-11-2025
 * @details Executes a non-blocking obstacle avoidance routine using
 * timed movement stages. The robot performs a sequence of turns and
 * short forward movements to bypass an obstacle and then resumes
 * normal operation.
 */
void obstacleAvoidance(int speed)
{

  static Timer t;      // duration of each movement step
  static int step = 0; // stage of the avoidance sequence

  // Start avoidance routine
  if (!avoiding)
  {
    avoiding = true;   // Mark that avoidance mode has begun
    step = 0;          // Reset step sequence to the first movement
    t.resetInterval(); // Reset the timer to ensure timings start fresh
    return;
  }

  switch (step)
  {

  // turn left
  case 0:
    moveSpeed(-150, speed);

    if (t.interval(400))
    { // after 400 ms
      step++;
      t.resetInterval();
    }
    break;

  // move forward
  case 1:
    moveSpeed(speed, speed);

    if (t.interval(100))
    { // after 100 ms
      step++;
      t.resetInterval();
    }
    break;

  // turn right
  case 2:
    moveSpeed(speed, 160);

    if (t.interval(200))
    { // after 200 ms
      step++;
      t.resetInterval();
    }
    break;

  // move forward
  case 3:
    moveSpeed(speed, 120);

    if (t.interval(400))
    {           // After 200 ms
      step = 7; // end of avoidng; go to last case;
      t.resetInterval();
    }
    break;

  // turn right
  case 4:
    moveSpeed(160, speed);

    if (t.interval(200))
    { // After 200 ms
      step++;
      t.resetInterval();
    }
    break;

  // move forward
  case 5:
    moveStabilized(speed, speed);

    if (t.interval(200))
    { // After 200 ms
      step++;
      t.resetInterval();
    }
    break;

  // turn left
  case 6:
    moveStabilized(-150, speed);

    if (t.interval(400))
    { // After 400 ms
      step++;
      t.resetInterval();
    }
    break;

  case 7:
    avoiding = false;
    break;
  }
}