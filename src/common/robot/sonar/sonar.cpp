#include "sonar.h"

bool avoiding = false;

/**
 * @name setupSonar
 * @author Francisco
 * @date 15-11-2025
 * @details Initializes the ultrasonic sensor (HC-SR04) by configuring the TRIG
 * pin as OUTPUT and the ECHO pin as INPUT. This setup enables the robot to send
 * ultrasonic pulses and detect their reflections for distance measurement.
 */

void setupSonar()
{
  pinMode(PIN_SONAR_TRIG, OUTPUT);                          // send ultrasonic pulses
  pinMode(PIN_SONAR_ECHO, INPUT);                           // receive reflected signal
}

/**
 * @name getDistanceCM
 * @author Francisco
 * @date 15-11-2025
 * @details Sends a trigger pulse to the ultrasonic sensor and measures the time
 * taken for the reflected echo to return. This duration is then converted into
 * an estimated distance in centimeters based on the speed of sound.
 * @details The result represents the distance to the nearest object directly
 * in front of the sensor. A value of 0 usually indicates an invalid or missing echo.
 * @return float  Estimated distance in centimeters
 */

float getDistanceCM()
{
  digitalWrite(PIN_SONAR_TRIG, LOW);                        // Ensure TRIG is low to start clean pulse
  delayMicroseconds(2);                                     // Short delay to stabilize the pin
  digitalWrite(PIN_SONAR_TRIG, HIGH);                       // Send a HIGH pulse to trigger the ultrasonic burst
  delayMicroseconds(10);                                    // Pulse duration: 10 microseconds (required by HC-SR04)
  digitalWrite(PIN_SONAR_TRIG, LOW);                        // Stop the trigger pulse

  unsigned long duration = pulseIn(PIN_SONAR_ECHO, HIGH);   // Measure the time until echo is received (in microseconds)

  float distance = duration * 0.034 / 2;
  return distance;
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
    static Timer t;                                         // duration of each movement step
    static int step = 0;                                    // stage of the avoidance sequence 

    // Start avoidance routine
    if (!avoiding) {           
        avoiding = true;                                    // Mark that avoidance mode has begun
        step = 0;                                           // Reset step sequence to the first movement
        t.resetInterval();                                  // Reset the timer to ensure timings start fresh
        return;                                             
    }

    // Execute movements depending on the current step
    switch (step) {
        
    // turn left
    case 0:  
        switchDirection(40, 100);                       // Left curve
        if (t.interval(800)) {                          // After 800 ms
            step++;                                     // Proceed to next movement
            t.resetInterval();                          
        }
        break;
        
    // turn right
    case 1:  
        switchDirection(100, 40);                       // Right curve
        if (t.interval(800)) {                          // After 800 ms
            step++;                                     
            t.resetInterval();                          
        }
        break;
        
    // move forward
    case 2:  
        moveForward(100);                               // move forward
        if (t.interval(800)) {                          // After 800 ms
            step++;                                     
            t.resetInterval();                          
        }
        break;
        
    // long right curve
    case 3:  
        switchDirection(100, 40);                       // right curve
        if (t.interval(1000)) {                         // After 1000 ms
            step++; 
            t.resetInterval();      
        }
        break;
    
    // long left curve
    case 4:  
        switchDirection(40, 100);                       // left curve
        if (t.interval(1000)) {                         // After 1000 ms
            step++; 
            t.resetInterval();      
        }
        break;
        
    // short forward movement
    case 5:  
        moveForward(100);                               // Move forward 
        if (t.interval(1000)) {                         // After 1000 ms
            step++; 
            t.resetInterval();      
        }
        break;
        
    // stop
    case 6:  
        stopMotors();                      
        avoiding = false;                  
        break;
    }
}


