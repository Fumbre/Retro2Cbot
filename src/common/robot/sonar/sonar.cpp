#include "sonar.h"

/**
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Configures the TRIG and ECHO pins of the ultrasonic sensor (HC-SR04).
 * @details TRIG is set as OUTPUT and is responsible for sending ultrasonic pulses.
 * @details ECHO is set as INPUT and is responsible for receiving the reflected signal.
 * @details Must be executed inside setup() before calling any distance-reading functions.
*/
void setupSonar()
{
  pinMode(PIN_SONAR_TRIG, OUTPUT); // TRIG pin set as output 
  pinMode(PIN_SONAR_ECHO, INPUT);  // ECHO pin set as input 
}

/**
 * @name getDistanceCM
 * @author Francisco
 * @date 15-11-2025
 * @details Sends an ultrasonic trigger pulse through the TRIG pin and measures
 * the time it takes for the echo to return through the ECHO pin.
 * @details The measured duration (in microseconds) is converted into a distance (cm)
 * using the approximate speed of sound (≈0.034 cm/µs) and dividing by 2
 * because the pulse travels to the obstacle and back.
 * @details The returned value corresponds to the estimated distance to the nearest
 * object directly in front of the sensor.
 * @return float: Distance in centimeters
*/
float getDistanceCM()
{
  digitalWrite(PIN_SONAR_TRIG, LOW);            // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);                         // Short delay to stabilize the pin
  digitalWrite(PIN_SONAR_TRIG, HIGH);           // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);                        // Pulse duration: 10 microseconds (required by HC-SR04)
  digitalWrite(PIN_SONAR_TRIG, LOW);            // Stop the trigger pulse

  unsigned long duration = pulseIn(PIN_SONAR_ECHO, HIGH);   // Measure the time until echo is received (in microseconds)

  float distance = duration * 0.034 / 2;
  return distance;
}

/**
 * @name isObstacleDetected
 * @author Francisco
 * @date 15-11-2025
 * @param limit_cm  Maximum distance (in cm) considered as an obstacle
 * @details Calls getDistanceCM() to obtain the current measured distance and
 * compares it to the user-defined threshold.
 * @details If the measured distance is less than or equal to limit_cm and greater
 * than 0 (valid reading), the function considers that an obstacle is present.
 * @return true if an obstacle is detected, false otherwise
*/
bool isObstacleDetected(float limit_cm)
{
  float distance = getDistanceCM();              // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0); // True if within limit and a valid reading (>0)
}

/**
 * @name startAvoidObstacle
 * @author Francisco
 * @date 16-11-2025
 * @details Starts the obstacle avoidance sequence using a non-blocking state machine.
 * @return nothing
*/

int currentAvoidsStatus = -1;     // -1 = noAction, 0-6 = active steps
Timer durationCurrentPhase;

void startAvoidObstacle()
{
  currentAvoidsStatus = 0;                    // Start avoidance sequence at phase 0
  durationCurrentPhase.hardReset();           // Reset timer for the first phase
}

/**
 * @name avoidObstacleStep
 * @author Francisco
 * @date 16-11-2025
 * @details Executes one step of the non-blocking obstacle avoidance routine.
 * @return bool: True if the robot is currently avoiding an obstacle.
 */

bool avoidObstacleStep()
{
  // If status is negative, no avoidance is active
  if (currentAvoidsStatus < 0)
    return false;                                     // Not avoiding

  switch (currentAvoidsStatus)
  {
    case 0:
      rotateLeft(200);                                // Phase 0: rotate left
      if (durationCurrentPhase.timeout(600))          // After 600 ms, move to next phase
      {
        currentAvoidsStatus = 1;
        durationCurrentPhase.hardReset();             // Restart timer for next phase
      }
      return true;

    case 1:
      moveForward(200);                               // Phase 1: move forward shortly
      if (durationCurrentPhase.timeout(700))
      {
        currentAvoidsStatus = 2;
        durationCurrentPhase.hardReset();
      }
      return true;

    case 2:
      rotateRight(200);                               // Phase 2: rotate right
      if (durationCurrentPhase.timeout(600))
      {
        currentAvoidsStatus = 3;
        durationCurrentPhase.hardReset();
      }
      return true;

    case 3:
      moveForward(200);                               // Phase 3: long forward movement
      if (durationCurrentPhase.timeout(5000))
      {
        currentAvoidsStatus = 4;
        durationCurrentPhase.hardReset();
      }
      return true;

    case 4:
      rotateRight(200);                               // Phase 4: rotate right again
      if (durationCurrentPhase.timeout(600))
      {
        currentAvoidsStatus = 5;
        durationCurrentPhase.hardReset();
      }
      return true;

    case 5:
      moveForward(200);                               // Phase 5: short forward movement
      if (durationCurrentPhase.timeout(700))
      {
        currentAvoidsStatus = 6;
        durationCurrentPhase.hardReset();
      }
      return true;

    case 6:
      rotateLeft(200);                                // Final phase: rotate left
      if (durationCurrentPhase.timeout(600))
      {
        currentAvoidsStatus = -1;                     // Sequence finished, return to normal mode
        durationCurrentPhase.hardReset();
      }
      return true;
  }

  return false;         
}