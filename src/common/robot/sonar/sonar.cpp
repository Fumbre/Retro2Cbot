#include "sonar.h"

/**
 * @name setupSonar
 * @authors Francisco
 * @date 11-12-2025
 * @details Initializes sonar pins depending on the robot model.
 * @details For BB011: uses shared trigger and three echo pins (front, right, left).
 * @details For other robots: uses one trigger and one front echo.
*/

void setupSonar() {
#if defined(BB011)
    pinMode(PIN_SONAR_TRIG, OUTPUT);
    pinMode(PIN_SONAR_ECHO_FRONT, INPUT);
    pinMode(PIN_SONAR_ECHO_RIGHT, INPUT);
    pinMode(PIN_SONAR_ECHO_LEFT, INPUT);
#else
    pinMode(PIN_SONAR_TRIG, OUTPUT);
    pinMode(PIN_SONAR_ECHO_FRONT, INPUT);
#endif
}

/**
 * @name measureDistance
 * @authors Francisco
 * @date 11-12-2025
 * @param echo Pin number of the sonar echo
 * @details Triggers the sonar pulse and measures the echo duration.
 * @details Uses a 15 ms timeout (~250 cm max range) for faster measurements.
 * @return float Distance in centimeters; returns 400.0 if no echo is detected.
*/

float measureDistance(int echo) {
#if defined(BB011)
    delay(35); 
#endif
    digitalWrite(PIN_SONAR_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_SONAR_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_SONAR_TRIG, LOW);

    unsigned long duration = pulseIn(echo, HIGH, 15000);

    if (duration == 0) return 400.0;

    return duration * 0.0343 / 2;
}

/**
 * @name getDistanceCM_Front
 * @authors Francisco
 * @date 11-12-2025
 * @details Measures the distance from the front sonar 
 * and stores it in sonarSendDatafrontDistance.
 * @return float Distance in centimeters
*/

float getDistanceCM_Front() {
    float distance = measureDistance(PIN_SONAR_ECHO_FRONT);
    sonarSendDatafrontDistance = distance;
    return distance;
}

/**
 * @name getDistanceCM_Right
 * @authors Francisco
 * @date 11-12-2025
 * @details Measures the distance from the right sonar (BB011 only) 
 * and stores it in sonarSendDataRightDistance.
 * @return float Distance in centimeters; returns 400.0 for robots without right sonar
*/

float getDistanceCM_Right() {
#if defined(BB011)
    float distance = measureDistance(PIN_SONAR_ECHO_RIGHT);
    sonarSendDataRightDistance = distance;
    return distance;
#else
    return 400.0;
#endif
}

/**
 * @name getDistanceCM_Left
 * @authors Francisco
 * @date 11-12-2025
 * @details Measures the distance from the left sonar (BB011 only) 
 * and stores it in sonarSendDataLeftDistance.
 * @return float Distance in centimeters; returns 400.0 for robots without left sonar
*/

float getDistanceCM_Left() {
#if defined(BB011)
    float distance = measureDistance(PIN_SONAR_ECHO_LEFT);
    sonarSendDataLeftDistance = distance;
    return distance;
#else
    return 400.0;
#endif
}

/**
 * @name isObstacleFront
 * @authors Francisco
 * @date 11-12-2025
 * @param limit Maximum distance to consider as obstacle (cm)
 * @details Checks if there is an obstacle in front within a certain distance range.
 * @return bool True if an obstacle is detected, otherwise false
*/

bool isObstacleFront(float limit) {
    float d = getDistanceCM_Front();
    return (d > 2.0 && d <= limit);
}

/**
 * @name isObstacleRight
 * @authors Francisco
 * @date 11-12-2025
 * @param limit Maximum distance to consider as obstacle (cm)
 * @details Checks if there is an obstacle to the right within a certain distance range.
 * @return bool True if an obstacle is detected, otherwise false
*/

bool isObstacleRight(float limit) {
    float d = getDistanceCM_Right();
    return (d > 2.0 && d <= limit);
}

/**
 * @name isObstacleLeft
 * @authors Francisco
 * @date 11-12-2025
 * @param limit Maximum distance to consider as obstacle (cm)
 * @details Checks if there is an obstacle to the left within a certain distance range.
 * @return bool True if an obstacle is detected, otherwise false
*/

bool isObstacleLeft(float limit) {
    float d = getDistanceCM_Left();
    return (d > 2.0 && d <= limit);
}
