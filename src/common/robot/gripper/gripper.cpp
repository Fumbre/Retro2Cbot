#include "gripper.h"

/**
 * @name gripper
 * @authors Francisco
 * @date 3-12-2025
 * @details Configures the gripper control pin and ensures
 * the servo signal starts in a safe LOW state.
*/

void setupGripper() {
    pinMode(GRIPPER, OUTPUT);
    digitalWrite(GRIPPER, LOW);
}

/**
 * @name gripper
 * @authors Francisco
 * @date 3-12-2025
 * @details Generates non-blocking servo control pulses in software to control a gripper.
 * @details Maintains a 20 ms interval between pulses, ensuring correct servo operation.
 * @param pulseMicroseconds Pulse width in microseconds that sets the gripper position.
 *  - Typical range for standard servos: 1000 µs (fully closed) to 2000 µs (fully open).
 *  - If pulseMicroseconds <= 0, the last set pulse is maintained.
 * @note This function should be called repeatedly in the main loop to continuously control the servo.
*/

void gripper(int pulseMicroseconds) {
    static unsigned long nextPulseTime = 0; 
    static int lastPulse = 2000;            

    if (pulseMicroseconds > 0) {            
        lastPulse = pulseMicroseconds; 
    }

    unsigned long now = millis(); 

    if (now >= nextPulseTime) {                
        nextPulseTime = now + 20; 

        digitalWrite(GRIPPER, HIGH); 
        delayMicroseconds(lastPulse); 
        digitalWrite(GRIPPER, LOW);   
    }
}

/**
 * @name gripperCatch
 * @authors Francisco
 * @date 3-12-2025
 * @details Closes the gripper.
*/

void gripperCatch() {

    gripper(1000); 
    gripperStatus = true;
}

void gripperUnCatch() {
    gripper(2000); 
    gripperStatus = false;
}
