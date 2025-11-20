#include "sonar.h"

// Timers for non-blocking obstacle avoidance
Timer avoidTimer;
bool avoiding = false;
int avoidStep = 0;

/**
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Initializes the ultrasonic sensor (HC-SR04) by configuring the TRIG
 * pin as OUTPUT and the ECHO pin as INPUT. This setup enables the robot to send
 * ultrasonic pulses and detect their reflections for distance measurement.
 */

void setupSonar()
{
  pinMode(PIN_SONAR_TRIG, OUTPUT); // send ultrasonic pulses
  pinMode(PIN_SONAR_ECHO, INPUT);  // receive reflected signal
}

/**
 * @name getDistanceCM
 * @author Francisco
 * @date 15-11-2025
 * @details Sends a trigger pulse to the ultrasonic sensor and measures the time
 * taken for the reflected echo to return. This duration is then converted into
 * an estimated distance in centimeters based on the speed of sound.
 * @details The result represents the distance to the nearest object directly
 * in front of the sensor. A value of 0 usually indicates an invalid or missing echo.
 * @return float  Estimated distance in centimeters
 */

float getDistanceCM()
{
  digitalWrite(PIN_SONAR_TRIG, LOW);  // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);               // Short delay to stabilize the pin
  digitalWrite(PIN_SONAR_TRIG, HIGH); // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);              // Pulse duration: 10 microseconds (required by HC-SR04)
  digitalWrite(PIN_SONAR_TRIG, LOW);  // Stop the trigger pulse

  unsigned long duration = pulseIn(PIN_SONAR_ECHO, HIGH); // Measure the time until echo is received (in microseconds)

  float distance = duration * 0.034 / 2;
  return distance;
}

/**
 * @name isObstacleDetected
 * @author Francisco
 * @date 15-11-2025
 * @param limit_cm  Maximum distance (in cm) used to define what counts as an obstacle
 * @details Reads the current distance using getDistanceCM() and compares it with
 * the user-defined threshold. If the measured distance is positive and less than
 * or equal to the limit, the function considers that an obstacle is present.
 * @return bool: true if an obstacle is detected, false otherwise
 */

bool isObstacleDetected(float limit_cm)
{
  float distance = getDistanceCM();              // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0); // True if within limit and a valid reading (>0)
}

/**
 * @name avoidObstacleSmoothNonBlocking
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

void avoidObstacleSmoothNonBlocking(int speed)
{
  if (!avoiding)
  {
    avoiding = true;
    avoidStep = 0;
    avoidTimer.resetInterval();
  }

  int curveTime = 900;         // time of each curve
  float curveStrengthL = 0.15; // left curve strength
  float curveStrengthR = 0.10; // right curve stronger
  int forwardTime = 500;       // straight segment

  switch (avoidStep)
  {

  // left curve
  case 0:
    switchDirection(speed * curveStrengthL, speed); // Set left motor speed lower

    if (avoidTimer.interval(curveTime))
    {                             // If the time allocated for the left curve has passed
      avoidStep = 1;              // move to the next step
      avoidTimer.resetInterval(); // reset the timer for the next phase
    }
    break;

  // forward
  case 1:
    moveForward(speed); // Drive both motors forward at the given speed

    if (avoidTimer.interval(forwardTime))
    {                             // If the forward interval has elapsed
      avoidStep = 2;              // move to the next step
      avoidTimer.resetInterval(); // reset timer for the next phase
    }
    break;

  // right curve
  case 2:
    switchDirection(speed, speed * curveStrengthR); // Lower right motor speed
    if (avoidTimer.interval(curveTime))
    {                             // If the time allocated for the right curve has passed
      avoidStep = 3;              // move to the final step
      avoidTimer.resetInterval(); // reset timer
    }
    break;

  case 3:
    moveForward(speed); // Continue moving straight ahead at normal speed
    avoiding = false;   // Mark that the robot is no longer in avoidance mode
    break;
  }
}
