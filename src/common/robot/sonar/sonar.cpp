#include "sonar.h"

#define SONAR_DELAY_MS 35   // tempo mínimo entre triggers

/*
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Configures the ultrasonic sensor pins used for distance measurement.
*/

void setupSonar()
{
    pinMode(PIN_SONAR_TRIG, OUTPUT);
    digitalWrite(PIN_SONAR_TRIG, LOW);

#if defined(BB011)
    pinMode(PIN_SONAR_ECHO_FRONT, INPUT);
    pinMode(PIN_SONAR_ECHO_LEFT, INPUT);
    pinMode(PIN_SONAR_ECHO_RIGHT, INPUT);
#else
    pinMode(PIN_SONAR_ECHO_FRONT, INPUT);
#endif
}

void sonarTrigger()
{
    digitalWrite(PIN_SONAR_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_SONAR_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_SONAR_TRIG, LOW);
}

float measureEcho(int echoPin)
{
    unsigned long duration = pulseIn(echoPin, HIGH, 25000);

    if (duration == 0) {
      return -1.0;
    }
        
    float distance = duration * 0.034 / 2.0;

    if (distance < 1.0 || distance > 300.0) {
      return -1.0;
    }
      
    return distance;
}

/*
 * @name getDistanceCM_Front
 * @author Francisco
 * @date 15-11-2025
 * @details Measures the distance to an obstacle in front of the robot.
*/

float getDistanceCM_Front()
{
    sonarTrigger();
    float d = measureEcho(PIN_SONAR_ECHO_FRONT);
    delay(SONAR_DELAY_MS);
    return d;
}

/*
 * @name getDistanceCM_Right
 * @author Francisco
 * @date 15-11-2025
 * @details Measures the distance to an obstacle on the right side.
*/

float getDistanceCM_Right() {

#if defined(BB011)
    sonarTrigger();
    float d = measureEcho(PIN_SONAR_ECHO_RIGHT);
    delay(SONAR_DELAY_MS);
    return d;
#else
    return -1.0;
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
    sonarTrigger();
    float d = measureEcho(PIN_SONAR_ECHO_LEFT);
    delay(SONAR_DELAY_MS);
    return d;
#else
    return -1.0;
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
