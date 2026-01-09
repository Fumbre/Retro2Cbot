#include "test_sonar.h"

/**
 * @name testSonar
 * @author Fumbre (Vladyslav)
 * @date 21-11-2025
 * @details make test for sonar
*/

void testSonar() {
    Serial.println(getDistanceCM_Front());
}

/**
 * @name testSonars
 * @author Uraib
 * @date 19-12-2025
 * @details make 3 sonars tests
*/

void testSonars() {
    static Timer t;

    if (!t.intervalStart(400)) {
        return;
    }
        
    float f = getDistanceCM_Front();
    float l = getDistanceCM_Left();
    float r = getDistanceCM_Right();

    Serial.print("STATE | ");

    // front
    Serial.print("F:");
    if (f > 1.0) {
        Serial.print(f, 2);
    } else {
        Serial.print("X");
    }
        
    // left
    Serial.print("  L:");
    if (l > 1.0) {
        Serial.print(l, 2);
    } else {
        Serial.print("X");
    }
        
    // right
    Serial.print("  R:");
    if (r > 1.0) {
        Serial.print(r, 2);
    } else {
        Serial.print("X");
    }
        
    // visual flags
    Serial.print(" | [");

    // Front obstacle
    if (f > 1.0 && f < 18.0) {
        Serial.print("F");
    } else {
        Serial.print(".");
    }
        
    // Left obstacle
    if (l > 1.0 && l < 15.0) {
        Serial.print("L");
    } else {
        Serial.print(".");
    }
        
    // Right obstacle
    if (r > 1.0 && r < 15.0) {
        Serial.print("R");
    } else {
        Serial.print(".");
    }
    Serial.println("]");
}
