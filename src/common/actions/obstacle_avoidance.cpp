#include "obstacle_avoidance.h"

bool avoiding = false;

/**
 * @name obstacleAvoidance
 * @author Francisco
 * @date 20-11-2025
 * @details Executes a smooth, non-blocking obstacle avoidance maneuver using
 * timed stages. The function progresses through each step based on interval
 * checks, allowing the robot to keep responding to other events while the
 * maneuver is running.
 * @details The avoidance sequence is as follows:
 *  1. perform a smooth left curve for a defined duration
 *  2. move forward for a short straight segment
 *  3. perform a smooth right curve for the same duration
 *  4. resume normal forward movement and finish the avoidance
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

  // Execute movements depending on the current step
  switch (step)
  {

  // turn left
  case 0:
    moveSpeed(-150, speed);
    // switchDirection(40, 100); // Left curve
    if (t.interval(400))
    {         // After 800 ms
      step++; // Proceed to next movement
      t.resetInterval();
    }
    break;

  // turn right
  case 1:
    moveSpeed(speed, speed);

    // switchDirection(100, 40); // Right curve
    if (t.interval(100))
    { // After 800 ms
      step++;
      t.resetInterval();
    }
    break;

  // move forward
  case 2:
    moveSpeed(speed, 160); // move forward
    if (t.interval(200))
    { // After 800 ms
      step++;
      t.resetInterval();
    }
    break;

  // long right curve
  case 3:
    moveSpeed(speed, 120);
    // switchDirection(100, 40); // right curve
    if (t.interval(400))
    { // After 1000 ms
      step = 6;
      t.resetInterval();
    }
    break;

  // long left curve
  case 4:
    moveSpeed(160, 255);
    // switchDirection(40, 100); // left curve
    if (t.interval(1000))
    { // After 1000 ms
      step = 6;
      // step++;
      t.resetInterval();
    }
    break;

  // short forward movement
  case 5:
    moveStabilized(255, 255); // move forward
    if (t.interval(200))
    { // After 1000 ms
      step++;
      t.resetInterval();
    }
    break;

  // stop
  case 6:
    // stopMotors();
    avoiding = false;
    break;
  }
}