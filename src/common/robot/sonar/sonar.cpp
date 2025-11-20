#include "sonar.h"

// Timers for non-blocking obstacle avoidance
Timer avoidTimer;
bool avoiding = false;  
int avoidStep = 0;

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

void avoidObstacleSmoothNonBlocking(int speed) {
  if (!avoiding) {
      avoiding = true;
      avoidStep = 0;
      avoidTimer.resetInterval();
  }

  int curveTime = 900;          // time of each curve
  float curveStrengthL = 0.15;  // left curve strength
  float curveStrengthR = 0.10;  // right curve stronger 
  int forwardTime = 500;        // straight segment

  switch (avoidStep) {                         
    
    // left curve
    case 0:                       
      switchDirection(speed * curveStrengthL, speed);  // Set left motor speed lower 
                                  
      if (avoidTimer.interval(curveTime)) {            // If the time allocated for the left curve has passed
          avoidStep = 1;                               // move to the next step
          avoidTimer.resetInterval();                  // reset the timer for the next phase
      }
      break;                                   
  
    // forward
    case 1:                          
      moveForward(speed);                              // Drive both motors forward at the given speed

      if (avoidTimer.interval(forwardTime)) {          // If the forward interval has elapsed
          avoidStep = 2;                               // move to the next step 
          avoidTimer.resetInterval();                  // reset timer for the next phase
      }
      break;                                   
    
    // right curve 
    case 2:                     
      switchDirection(speed, speed * curveStrengthR);     // Lower right motor speed 
      if (avoidTimer.interval(curveTime)) {               // If the time allocated for the right curve has passed
          avoidStep = 3;                                  // move to the final step
          avoidTimer.resetInterval();                     // reset timer 
      }
      break;                                   

    case 3:                             
      moveForward(speed);                                 // Continue moving straight ahead at normal speed
      avoiding = false;                                   // Mark that the robot is no longer in avoidance mode
      break;                                   
  }
}                                             

