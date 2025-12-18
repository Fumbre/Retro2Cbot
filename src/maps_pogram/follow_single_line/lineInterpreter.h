#pragma once
#include <Arduino.h>

enum LineState {
    CENTER,
    SLIGHT_LEFT,
    SLIGHT_RIGHT,
    HARD_LEFT,
    HARD_RIGHT,
    
    ALL_WHITE,     
    ALL_BLACK,      
    
    LEFT_TURN,      
    RIGHT_TURN,
    
    TEST_PATTERN,
};


class LineInterpreter {
public:
    LineState interpret(uint8_t mask);

private:
    bool match(uint8_t mask, const uint8_t* patterns, int count);
};
