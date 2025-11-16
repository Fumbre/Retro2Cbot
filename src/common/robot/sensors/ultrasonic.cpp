#include "ultrasonic.h"

/**
 * @name setupUltrasonicSensor
 * @author Francisco
 * @date 13.11.2025
 * @details Initialize ultrasonic pins
 */
void setupUltrasonicSensor()
{
  pinMode(PIN_SONAR_TRIG, OUTPUT); // TRIG pin set as output to send ultrasonic pulses
  pinMode(PIN_SONAR_ECHO, INPUT);  // ECHO pin set as input to receive reflected signal
}

/**
 * @name getDistanceCM
 * @author Francisco
 * @date 13.11.2025
 * @details Measure distance in cm
 * @return float
 */
float getDistanceCM()
{
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
 * @date 13.11.2025
 * @details Return true if obstacle detected (within threshold)
 * @return bool
 */
bool isObstacleDetected(float limit_cm)
{
  float distance = getDistanceCM();              // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0); // True if within limit and a valid reading (>0)
}
