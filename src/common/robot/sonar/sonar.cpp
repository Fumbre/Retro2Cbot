#include "sonar.h"

/*
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Configures the ultrasonic sensor pins used for distance measurement.
*/

void setupSonar() {

#if defined(BB011)
  pinMode(PIN_SONAR_TRIG, OUTPUT);                    // Shared Trigger
  pinMode(PIN_SONAR_ECHO_FRONT, INPUT);                     
  pinMode(PIN_SONAR_ECHO_RIGHT, INPUT);               
  pinMode(PIN_SONAR_ECHO_LEFT, INPUT);                
#else
  pinMode(PIN_SONAR_TRIG, OUTPUT);                    
  pinMode(PIN_SONAR_ECHO_FRONT, INPUT);              
#endif
}

/*
 * @name measureDistance
 * @author Francisco
 * @date 15-11-2025
 * @param echo Echo pin connected to the ultrasonic sensor.
 * @details Sends an ultrasonic pulse and measures the returned echo
 * to calculate the distance (cm).
*/

float measureDistance(int echo) {

  // Clean trigger pulse
  digitalWrite(PIN_SONAR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONAR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIG, LOW);

  // Read the bounce back
  unsigned long duration = pulseIn(echo, HIGH, 25000);          // timeout 25ms

  // If no echo (0) or out of range, return 400
  if (duration == 0 || duration > 23200) {
    return 400.0;
  }
  return duration * 0.034 / 2;
}

/*
 * @name getDistanceCM_Front
 * @author Francisco
 * @date 15-11-2025
 * @details Measures the distance to an obstacle in front of the robot.
*/

float getDistanceCM_Front() {
  return measureDistance(PIN_SONAR_ECHO_FRONT);
}

/*
 * @name getDistanceCM_Right
 * @author Francisco
 * @date 15-11-2025
 * @details Measures the distance to an obstacle on the right side.
*/

float getDistanceCM_Right() {
#if defined(BB011)
  return measureDistance(PIN_SONAR_ECHO_RIGHT);
#else
  return 0;
#endif
}

/*
 * @name getDistanceCM_Left
 * @author Francisco
 * @date 15-11-2025
 * @details Measures the distance to an obstacle on the left side.
*/

float getDistanceCM_Left() {
#if defined(BB011)
  return measureDistance(PIN_SONAR_ECHO_LEFT);
#else
  return 0;
#endif
}

/*
 * @name isObstacleFront
 * @author Francisco
 * @date 15-11-2025
 * @param Maximum distance limit (cm).
 * @details Checks if there is an obstacle in front within a given range.
*/

bool isObstacleFront(float limit) {

  float d = getDistanceCM_Front();
  return (d > 1.0 && d <= limit);
}

/*
 * @name isObstacleRight
 * @author Francisco
 * @date 15-11-2025
 * @param Maximum distance limit (cm).
 * @details Checks if there is an obstacle on the right within a given range.
*/

bool isObstacleRight(float limit) {

  float d = getDistanceCM_Right();
  return (d > 1.0 && d <= limit);
}

/*
 * @name isObstacleLeft
 * @author Francisco
 * @date 15-11-2025
 * @param Maximum distance limit (cm).
 * @details Checks if there is an obstacle on the left within a given range.
*/

bool isObstacleLeft(float limit) {

  float d = getDistanceCM_Left();
  return (d > 1.0 && d <= limit);
}
