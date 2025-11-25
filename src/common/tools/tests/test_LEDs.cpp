/**
 * @name testLEDs
 * @author Aria
 * @date 23-11-2025
 * @details leds, maybe, god willing, hopefully
 */

#include <Adafruit_NeoPixel.h>

// ===== PIN & LED SETTINGS =====
#define NEO_PIN ?   // to be defined
#define NUM_PIXELS 4

Adafruit_NeoPixel pixels(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

// ===== GLOBAL MOTOR STATE =====
int motorLeftSpeed = 0;
int motorRightSpeed = 0;
bool motorsRunning = false;

// ===== INTERNAL LIGHTING CONFIG =====
unsigned long blinkTimer = 0;
bool blinkState = false;
const int BLINK_INTERVAL = 250;
const int TURN_DIFF = 40;   // turning threshold    
// frankoly i dont know how we are going to measure this with the stuff we already have going on

// ===== INITIALIZATION =====
void initNeoPixels() {
    pixels.begin();
    pixels.show();
}

// ===== MAIN LIGHT UPDATE FUNCTION =====
void updateNeoPixels() {

    // ----- Determine robot state -----
    bool stopped = !motorsRunning;
    bool turningLeft = false;
    bool turningRight = false;

    if (motorsRunning) {
        if (motorLeftSpeed < motorRightSpeed - TURN_DIFF) {
            turningLeft = true;
        } 
        else if (motorRightSpeed < motorLeftSpeed - TURN_DIFF) {
            turningRight = true;
        }
    }

    // ----- Blink timing -----
    if (millis() - blinkTimer >= BLINK_INTERVAL) {
        blinkTimer = millis();
        blinkState = !blinkState;
    }

    // ----- Default = all green -----
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 40, 0));
    }

    // ----- Brake lights -----
    if (stopped) {
        pixels.setPixelColor(2, pixels.Color(40, 0, 0)); // rear-right
        pixels.setPixelColor(3, pixels.Color(40, 0, 0)); // rear-left
    }

    // ----- Turn signals -----
    if (turningLeft && blinkState) {
        pixels.setPixelColor(0, pixels.Color(60, 25, 0)); // amber front-left
    }

    if (turningRight && blinkState) {
        pixels.setPixelColor(1, pixels.Color(60, 25, 0)); // amber front-right
    }

    pixels.show();
}