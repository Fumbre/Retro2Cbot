#include "gripper.h"

/**
 * @name gripper
 * @authors Francisco
 * @date 3-12-2025
 * @details Configures the gripper control pin and ensures
 * the servo signal starts in a safe LOW state.
 */

void setupGripper()
{
    pinMode(GRIPPER, OUTPUT);
    digitalWrite(GRIPPER, LOW);
}

/**
 * @name gripper
 * @authors Francisco
 * @date 3-12-2025
 * @details Generates non-blocking servo control pulses in software.
 * @param pulseMicroseconds Pulse width in microseconds that sets
 * the gripper position (e.g. 1000–2000 µs).
 */

void gripper(int pulseMicroseconds)
{
    static unsigned long nextPulseTime = 0; // Stores the next time when a new servo pulse should be generated
    static int lastPulse = 2000;            // 2000 µs = gripper fully open

    if (pulseMicroseconds > 0)
    {                                  // If a new pulse width is provided (must be > 0)
        lastPulse = pulseMicroseconds; // Update the stored pulse width (1000–2000 µs for standard servos)
    }

    unsigned long now = millis(); // Read current time in ms since the program started

    if (now >= nextPulseTime)
    {                             // Only generate a pulse if 20 ms have passed
        nextPulseTime = now + 20; // Schedule the next pulse for 20 ms later

        digitalWrite(GRIPPER, HIGH);  // Start the HIGH pulse to signal the servo position
        delayMicroseconds(lastPulse); // Keep the pin HIGH for the exact duration of the desired pulse
        digitalWrite(GRIPPER, LOW);   // End the pulse—servo reads the pulse width to set its angle
    }
}

/**
 * @name gripperCatch
 * @authors Francisco
 * @date 3-12-2025
 * @details Closes the gripper.
 */

void gripperCatch()
{

    gripper(1000); // Close the gripper
    gripperStatus = true;
}

void gripperUnCatch()
{
    gripper(2000); // Open the gripper
    gripperStatus = false;
}
