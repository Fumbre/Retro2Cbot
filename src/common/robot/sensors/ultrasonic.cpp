#include <Arduino.h>
#include "../../constant/Robot.h"
#include "ultrasonic.h"

// Initialize ultrasonic pins
void initializeUltrasonicSensor() {
  pinMode(TRIG_PIN, OUTPUT);   // TRIG pin set as output to send ultrasonic pulses
  pinMode(ECHO_PIN, INPUT);    // ECHO pin set as input to receive reflected signal
}

// Measure distance in cm
float getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);       // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);              // Short delay to stabilize the pin
  
  digitalWrite(TRIG_PIN, HIGH);      // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);             // Pulse duration: 10 microseconds (required by HC-SR04)
  
  digitalWrite(TRIG_PIN, LOW);       // Stop the trigger pulse

  unsigned long duration = pulseIn(ECHO_PIN, HIGH);   // Measure the time until echo is received (in microseconds)

  // Convert time to distance:
  // speed of sound ≈ 0.034 cm/ms
  // divide by 2 because signal travels to the object and back
  // Return the distance in centimeters
  float distance = duration * 0.034 / 2;                                                                                                                      
  return distance;                                     
}

// Return true if obstacle detected (within threshold)
bool isObstacleDetected(float limit_cm) {
  float distance = getDistanceCM();                  // Read current distance from ultrasonic sensor
  return (distance <= limit_cm && distance > 0);     // True if within limit and a valid reading (>0)
}
