#pragma once
#include "Line_sensor.h"
#include "Line_Interrupter.h"

struct FollowerResult{
    Direction dir;
    Direction lastDir;
    int baseSpeed;
    int turnSpeed;
};

class LineFollower
{
private:
    int baseSpeed;
    int turnSpeed;
    Direction lastDir;

public:
    LineFollower(int baseSpeed, int turnSpeed)
    {
        this->baseSpeed = baseSpeed;
        this->turnSpeed = turnSpeed;
        this->lastDir = CENTER;
    }

    FollowerResult follow(LineSensor &sensor, LineInterpreter &interpreter)
    {
        LineReading reading = sensor.read();
        Direction dir = interpreter.interpret(reading.mask);
        if(dir != LOST){
            this->lastDir = dir;
        }
        FollowerResult result;
        result.dir = dir;
        result.baseSpeed = this->baseSpeed;
        result.turnSpeed = this->baseSpeed;
        result.lastDir = this->lastDir;
        return result;
    }
};