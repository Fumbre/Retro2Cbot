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
void setupSonar() {
  pinMode(PIN_SONAR_TRIG, OUTPUT); // TRIG pin set as output to send ultrasonic pulses
  pinMode(PIN_SONAR_ECHO, INPUT);  // ECHO pin set as input to receive reflected signal
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
 * @return float  Distance in centimeters
 */
float getDistanceCM() {
  digitalWrite(PIN_SONAR_TRIG, LOW); // Ensure TRIG is low to start clean pulse

  // TODO test and Check without using delay
  delayMicroseconds(2); // Short delay to stabilize the pin

  digitalWrite(PIN_SONAR_TRIG, HIGH); // Send a HIGH pulse to trigger the ultrasonic burst

  // TODO test and Check without using delay
  delayMicroseconds(10); // Pulse duration: 10 microseconds (required by HC-SR04)

  digitalWrite(PIN_SONAR_TRIG, LOW); // Stop the trigger pulse

  unsigned long duration = pulseIn(PIN_SONAR_ECHO, HIGH); // Measure the time until echo is received (in microseconds)

  // Convert time to distance:
  // speed of sound ≈ 0.034 cm/ms
  // divide by 2 because signal travels to the object and back
  // Return the distance in centimeters
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
bool isObstacleDetected(float limit_cm) {
  float distance = getDistanceCM();              // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0); // True if within limit and a valid reading (>0)
}

/**
 * @name avoidObstacle
 * @author Francisco
 * @date 15-11-2025
 * @details Function responsible for executing a predefined sequence of movements
 * whenever an obstacle is detected by the ultrasonic sensor.
 * @details The sequence is as follows:
 *  1) turn left
 *  2) move forward slightly
 *  3) turn right
 *  4) move forward for ~5s
 *  5) turn right again
 *  6) move forward slightly
 *  7) turn left
 *  8) continue straight ahead
 * @details This routine allows the robot to navigate around simple obstacles in a physical environment.
 * @return nothing
 */

// Timers for non-blocking obstacle avoidance
Timer avoidTimer;
bool avoiding = false;  
int avoidStep = 0;

void avoidObstacleSmoothNonBlocking(int speed) {
  if (!avoiding) {
      avoiding = true;
      avoidStep = 0;
      avoidTimer.resetInterval();
  }

  // PARAMETERS — change here to tune behavior
  int curveTime = 700;        // how long to curve each side (ms)
  float curveStrength = 0.25;  // how much slower one wheel goes (0.0–1.0)
  int forwardTime = 400;      // time to go straight between curves

  switch (avoidStep) {

    case 0: // Step 1: turn LEFT
      switchDirection(speed * curveStrength, speed);
      
      if (avoidTimer.interval(curveTime)) {
          avoidStep = 1;
          avoidTimer.resetInterval();
      }
      break;

    case 1: // Step 2: forward a little
      moveForward(speed);

      if (avoidTimer.interval(forwardTime)) {
          avoidStep = 2;
          avoidTimer.resetInterval();
      }
      break;

    case 2: // Step 3: turn RIGHT (exact mirror of left)
      switchDirection(speed, speed * curveStrength);

      if (avoidTimer.interval(curveTime)) {
          avoidStep = 3;
          avoidTimer.resetInterval();
      }
      break;

    case 3: // Step 4: resume normal movement
      moveForward(speed);
      avoiding = false;   // finished the bypass
      break;
  }
}



