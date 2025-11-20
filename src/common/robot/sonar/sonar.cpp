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
  pinMode(PIN_SONAR_TRIG_1, OUTPUT); // TRIG pin set as output 
  pinMode(PIN_SONAR_ECHO_1, INPUT);  // ECHO pin set as input 

    pinMode(PIN_SONAR_TRIG_2, OUTPUT); // TRIG pin set as output 
    pinMode(PIN_SONAR_ECHO_2, INPUT);  // ECHO pin set as input 
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
  digitalWrite(PIN_SONAR_TRIG_1, LOW);            // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);                         // Makes sure the pin is low
  digitalWrite(PIN_SONAR_TRIG_1, HIGH);           // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);                        // Pulse duration: 10 microseconds (required by HC-SR04)
  digitalWrite(PIN_SONAR_TRIG_1, LOW);            // Stop the trigger pulse

  unsigned long duration = pulseIn(PIN_SONAR_ECHO_1, HIGH);   // Measure the time until echo is received (in microseconds)

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
 * than 2 (valid reading), the function considers that an obstacle is present.
 * @return true if an obstacle is detected, false otherwise
*/
bool isObstacleDetected(float limit_cm)
{
  float distance = getDistanceCM();              // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 2); // True if within limit and a valid reading (>2)
}

/**
 * @name startAvoidObstacle
 * @author Francisco
 * @date 16-11-2025
 * @details Starts the obstacle avoidance sequence using a non-blocking state machine.
 * @return nothing
 */
// void avoidObstacle()
// {
//   // turn left
//   rotateLeft(200);
//   delay(600);

//   // move forward slightly
//   moveForward(200);
//   delay(700);

//   // turn right
//   rotateRight(200);
//   delay(600);

//   // move forward for ~5s
//   moveForward(200);
//   delay(5000);

//   // turn right again
//   rotateRight(200);
//   delay(600);

//   // move forward slightly
//   moveForward(200);
//   delay(700);

//   // turn left
//   rotateLeft(200);
//   delay(600);

//   // continue staright ahead
//   moveForward(200);
// }