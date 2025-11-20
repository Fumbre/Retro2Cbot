#include "gripper.h"

void setupGripper()
{
    pinMode(GRIPPER, OUTPUT);   // Set the gripper pin as an OUTPUT
    digitalWrite(GRIPPER, LOW); // Ensure the servo signal starts LOW
}

// TODO
// 1. add function declaration
// 2. create gripper Catch function and do not put param pulseMicroseconds because we would like to catch it once (every 20 pulses)
// 3. create gripper unCatch function to put object back
void gripper(int pulseMicroseconds)
{
    static unsigned long nextPulseTime = 0; // Stores the time when the next 20 ms cycle should start
    static int lastPulse = 2000;            // Stores the last valid pulse width (default = 2000 µs, fully open)

    // If a valid pulse width is given (>0), update the stored value
    if (pulseMicroseconds > 0)
    {
        lastPulse = pulseMicroseconds; // Save the new pulse width (1000–2000 µs)
    }

    unsigned long now = millis(); // Read current time in milliseconds

    // Only generate a servo pulse every 20 ms (the standard servo refresh rate = 50 Hz)
    if (now >= nextPulseTime)
    {
        nextPulseTime = now + 20; // Schedule the next pulse for 20 ms later

        digitalWrite(GRIPPER, HIGH);  // Start the HIGH pulse that tells the servo the position
        delayMicroseconds(lastPulse); // Keep the pulse HIGH for the exact time (pulse width)
        digitalWrite(GRIPPER, LOW);   // End the pulse (servo reads the duration to set the angle)
    }
}
