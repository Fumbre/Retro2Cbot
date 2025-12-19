#include <Arduino.h>

// 1. FORCE THE BOARD TYPE (Must be before other includes)
#define BB011

#include "common/robot/motor/motor.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"
#include "maps_pogram/physical_maze/physical_maze.h"
#include "common/robot/movement/movement.h"

// This lets the main file see what stage the maze is in
extern int mazeState;

void setup()
{
    // Standard baud rate for Serial Monitor
    Serial.begin(9600);

    // Initialize all hardware components
    setupMotor();
    setupSonar();
    setupGripper();

    // Initialize maze variables
    mazeInit();

    Serial.println("--- RELAYBOT READY: BB011 CONFIG ---");
    Serial.println("Logic: Clean moveSpeed | Sensor: Anti-Crosstalk");
}

void loop()
{
    // 1. Run the navigation brain
    // This calls getDistanceCM internally (with the 35ms delays)
    mazeStep();

    // 2. Log data every 400ms
    // Increased slightly to give sensors more breathing room
    static unsigned long lastLog = 0;
    if (millis() - lastLog > 400)
    {
        float f = getDistanceCM_Front();
        float r = getDistanceCM_Right();
        float l = getDistanceCM_Left();

        Serial.print("STATE:");
        Serial.print(mazeState);
        Serial.print(" | F:");
        Serial.print(f);
        Serial.print(" L:");
        Serial.print(l);
        Serial.print(" R:");
        Serial.print(r);

        // Visual Obstacle Check (Using 18cm as threshold)
        Serial.print(" | [");
        Serial.print(f < 18.0 ? "F" : " ");
        Serial.print(l < 15.0 ? "L" : " ");
        Serial.print(r < 15.0 ? "R" : " ");
        Serial.println("]");

        // DIAGNOSTIC: If sensors are still 400, print a warning
        if (f > 399 && r > 399 && l > 399)
        {
            Serial.println("!! SENSOR TIMEOUT: Check Pin 12 Trigger !!");
        }

        lastLog = millis();
    }
}