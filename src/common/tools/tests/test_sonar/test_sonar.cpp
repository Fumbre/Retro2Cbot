#include "test_sonar.h"

/**
 * @name testSonar
 * @author Fumbre (Vladyslav)
 * @date 21-11-2025
 * @details make test for sonar
 */
void testSonar()
{
    Serial.println(getDistanceCM_Front());
}

/**
 * @name testSonars
 * @author Uraib
 * @date 19-12-2025
 * @details make 3 sonars tests
 */
void testSonars()
{
    static Timer t;
    if (t.intervalStart(400))
    {
        float f = getDistanceCM_Front();
        float r = getDistanceCM_Right();
        float l = getDistanceCM_Left();

        Serial.print("STATE:");
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
    }
}
