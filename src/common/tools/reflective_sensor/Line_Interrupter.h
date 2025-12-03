#pragma once
#include <Arduino.h>

enum Direction
{
    CENTER,
    SLIGHT_LEFT,
    SLIGHT_RIGHT,
    HARD_LEFT,
    HARD_RIGHT,
    LOST
};

// --- bitmask tables ---
const uint8_t centerPatterns[] = {0b00011000, 0b00111100};
const uint8_t slightLeftPatterns[] = {0b00110000, 0b01110000, 0b00111000};
const uint8_t slightRightPatterns[] = {0b00001100, 0b00001110, 0b00011100};
const uint8_t hardLeftPatterns[] = {0b11100000, 0b11000000, 0b10000000};
const uint8_t hardRightPatterns[] = {0b00000111, 0b00000011, 0b00000001};
const uint8_t lostPatterns[] = {0b00000000, 0b11111111};

class LineInterpreter
{
public:
    Direction interpret(uint8_t mask)
    {
        if (match(mask, centerPatterns, sizeof(centerPatterns)))
            return CENTER;
        if (match(mask, slightLeftPatterns, sizeof(slightLeftPatterns)))
            return SLIGHT_LEFT;
        if (match(mask, slightRightPatterns, sizeof(slightRightPatterns)))
            return SLIGHT_RIGHT;
        if (match(mask, hardLeftPatterns, sizeof(hardLeftPatterns)))
            return HARD_LEFT;
        if (match(mask, hardRightPatterns, sizeof(hardRightPatterns)))
            return HARD_RIGHT;
        if (match(mask, lostPatterns, sizeof(lostPatterns)))
            return LOST;

        return CENTER; // default
    }

private:
    bool match(uint8_t mask, const uint8_t *patterns, int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (mask == patterns[i])
                return true;
        }
        return false;
    }
};