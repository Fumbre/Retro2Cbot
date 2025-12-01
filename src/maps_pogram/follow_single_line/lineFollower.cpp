// #include "lineFollower.h"
// #include "common/robot/movement/movement.h" // uses moveSpeed()

// // ----- Bitmask tables -----

// const uint8_t CENTER_PATTERNS[] = {
//   0b00011000,
//   0b00011100,
//   0b00111000
// };

// const uint8_t SLIGHT_LEFT_PATTERNS[] = {
//   0b00110000,
//   0b01110000
// };

// const uint8_t SLIGHT_RIGHT_PATTERNS[] = {
//   0b00001100,
//   0b00001110
// };

// const uint8_t HARD_LEFT_PATTERNS[] = {
//   0b11100000,
//   0b11000000
// };

// const uint8_t HARD_RIGHT_PATTERNS[] = {
//   0b00000111,
//   0b00000011
// };

// const uint8_t LOST_LINE_PATTERNS[] = {
//   0b00000000,
//   0b11111111
// };

// bool matchAny(uint8_t mask, const uint8_t* arr, int count) {
//     for (int i = 0; i < count; i++)
//         if (mask == arr[i]) return true;
//     return false;
// }

// LineFollower::LineFollower(int baseSpeed, int turnSpeed)
//   : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

// void LineFollower::follow(LineSensor& sensor) {

//     LineReading r = sensor.read();
//     uint8_t mask = r.mask;

//     // ----- CENTER -----
//     if (matchAny(mask, CENTER_PATTERNS,
//                  sizeof(CENTER_PATTERNS))) {
//         moveSpeed(baseSpeed, baseSpeed);
//         return;
//     }

//     // ----- SLIGHT LEFT -----
//     if (matchAny(mask, SLIGHT_LEFT_PATTERNS,
//                  sizeof(SLIGHT_LEFT_PATTERNS))) {
//         moveSpeed(baseSpeed * 0.5, baseSpeed);
//         return;
//     }

//     // ----- SLIGHT RIGHT -----
//     if (matchAny(mask, SLIGHT_RIGHT_PATTERNS,
//                  sizeof(SLIGHT_RIGHT_PATTERNS))) {
//         moveSpeed(baseSpeed, baseSpeed * 0.5);
//         return;
//     }

//     // ----- HARD LEFT -----
//     if (matchAny(mask, HARD_LEFT_PATTERNS,
//                  sizeof(HARD_LEFT_PATTERNS))) {
//         moveSpeed(-turnSpeed, turnSpeed);
//         return;
//     }

//     // ----- HARD RIGHT -----
//     if (matchAny(mask, HARD_RIGHT_PATTERNS,
//                  sizeof(HARD_RIGHT_PATTERNS))) {
//         moveSpeed(turnSpeed, -turnSpeed);
//         return;
//     }

//     // ----- LOST LINE -----
//     if (matchAny(mask, LOST_LINE_PATTERNS,
//                  sizeof(LOST_LINE_PATTERNS))) {
//         // simple recovery: rotate right
//         moveSpeed(baseSpeed, -baseSpeed);
//         return;
//     }
// }


// ============================================

#include "lineFollower.h"
#include "common/robot/movement/movement.h"
LineFollower::LineFollower(int baseSpeed, int turnSpeed)
    : baseSpeed(baseSpeed), turnSpeed(turnSpeed) {}

void LineFollower::follow(LineSensor& sensor, LineInterpreter& interpreter) {

    LineReading reading = sensor.read();
    Direction dir = interpreter.interpret(reading.mask);

    switch (dir) {
        case CENTER:
            moveSpeed(baseSpeed, baseSpeed);
            break;

        case SLIGHT_LEFT:
            moveSpeed(baseSpeed * 0.5, baseSpeed);
            break;

        case SLIGHT_RIGHT:
            moveSpeed(baseSpeed, baseSpeed * 0.5);
            break;

        case HARD_LEFT:
            moveSpeed(-turnSpeed, turnSpeed);
            break;

        case HARD_RIGHT:
            moveSpeed(turnSpeed, -turnSpeed);
            break;

        case LOST:
            moveSpeed(baseSpeed, -baseSpeed); // rotate right
            break;
    }
}
