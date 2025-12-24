#include "gripper.h"

/**
 * @name ReflectiveSensor
 * @authors Francisco
 * @date ?-1?-2025
 */
void setupGripper()
{
    pinMode(GRIPPER, OUTPUT);   // Set the gripper pin as an OUTPUT
    digitalWrite(GRIPPER, LOW); // Ensure the servo signal starts LOW
}

void gripper(int pulseMicroseconds)
{
    static unsigned long nextPulseTime = 0; // Stores the next time (in ms) when a new servo pulse should be generated
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

void gripperCatch()
{

    gripper(1000); // Close the gripper
}

void gripperUnCatch()
{

    gripper(2000); // Open the gripper
}
