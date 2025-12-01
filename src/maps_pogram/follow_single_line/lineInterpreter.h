#pragma once
#include <Arduino.h>

enum Direction {
    CENTER,
    SLIGHT_LEFT,
    SLIGHT_RIGHT,
    HARD_LEFT,
    HARD_RIGHT,
    LOST
};

class LineInterpreter {
public:
    Direction interpret(uint8_t mask);

private:
    bool match(uint8_t mask, const uint8_t* patterns, int count);
};
