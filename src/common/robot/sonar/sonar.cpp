#include <Arduino.h>
#include "common/robot/sonar/sonar.h"
#include "common/constant/motor.h"
#include "common/robot/movement/movement.h"

/**
 * @name initializeUltrasonicSensor
 * @author Francisco
 * @date 15-11-2025
 * @details Configures the TRIG and ECHO pins of the ultrasonic sensor (HC-SR04).
 * @details TRIG is set as OUTPUT and is responsible for sending ultrasonic pulses.
 * @details ECHO is set as INPUT and is responsible for receiving the reflected signal.
 * @details Must be executed inside setup() before calling any distance-reading functions.
 * @return nothing
*/

void initializeUltrasonicSensor() {
  pinMode(TRIG_PIN, OUTPUT);                // TRIG pin set 
  pinMode(ECHO_PIN, INPUT);                 // ECHO pin set
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
  digitalWrite(TRIG_PIN, LOW);                        // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);                               // Short delay to stabilize the pin
  
  digitalWrite(TRIG_PIN, HIGH);                       // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);                              // Pulse duration: 10 microseconds (required by HC-SR04)
  
  digitalWrite(TRIG_PIN, LOW);                        // Stop the trigger pulse

  unsigned long duration = pulseIn(ECHO_PIN, HIGH);   // Measure the time until echo is received (in microseconds)

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
  float distance = getDistanceCM();                  // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0);     
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

void avoidObstacle()
{
  // turn left
  rotateLeft(200);
  delay(600);

  // move forward slightly
  moveForward(200);
  delay(700);

  // turn right
  rotateRight(200);
  delay(600);

  // move forward for ~5s
  moveForward(200);
  delay(5000);

  // turn right again
  rotateRight(200);
  delay(600);

  // move forward slightly
  moveForward(200);
  delay(700);

  // turn left
  rotateLeft(200);
  delay(600);

  // continue staright ahead
  moveForward(200);
}

