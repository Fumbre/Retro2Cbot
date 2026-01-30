/**
 * @name functions of object avoidance
 * @author Francisco
 * @date 20-11-2025
*/

#include "obstacle_avoidance.h"

bool avoiding = false;

/**
 * @name obstacleAvoidance
 * @author Francisco
 * @date 20-11-2025
 * @details  Executes a non-blocking obstacle avoidance routine using
 * timed movement stages. The robot performs a sequence of turns and
 * short forward movements to bypass an obstacle and then resumes
 * normal operation.
*/

void obstacleAvoidance(int speed) {

  static Timer t;                   // Duration of each movement step
  static int step = 0;              // Stage of the avoidance sequence

  // Start avoidance routine
  if (!avoiding) {
    avoiding = true;                // Mark that avoidance mode has begun
    step = 0;                       // Reset step sequence to the first movement
    t.resetInterval();              // Reset the timer to ensure timings start fresh
    return;
  }

  switch (step) {

  // Turn left
  case 0:
    moveSpeed(-150, speed);

    if (t.interval(250)) {          // After 250 ms
      step++;
      t.resetInterval();
    }
    break;

  // Move forward
  case 1:
    moveSpeed(speed, speed);

    if (t.interval(150)) {          // After 150 ms
      step++;
      t.resetInterval();
    }
    break;

  // Turn right
  case 2:
    moveSpeed(speed, -150);

    if (t.interval(100)) {          // After 100 ms
      step++;
      t.resetInterval();
    }
    break;

  // Move forward
  case 3:
    moveSpeed(speed, 160);          

    if (t.interval(200)) {          // After 200 ms
      step = 4;                     // End of avoidng
      t.resetInterval();
    }
    break;

  case 4:
    avoiding = false;
    break;
  }
}
