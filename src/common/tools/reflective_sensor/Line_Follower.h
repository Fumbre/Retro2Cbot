#pragma once
#include "Line_sensor.h"
#include "Line_Interrupter.h"

struct FollowerResult{
    Direction dir;
    Direction lastDir;
    float speedFactor;
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
    LineFollower()
    {
        this->lastDir = CENTER;
    }

    void setupPWMValue(int baseSpeed){
        this->baseSpeed = baseSpeed - 50;
        this->turnSpeed = baseSpeed;
    }

    FollowerResult follow(LineSensor &sensor, LineInterpreter &interpreter)
    {
        LineReading reading = sensor.read();
        Direction dir = interpreter.interpret(reading.mask);
        if(dir != LOST){
            this->lastDir = dir;
        }
        //set reducing factor
        float factor = 1;
        if(dir == SLIGHT_LEFT || dir == SLIGHT_RIGHT){
            factor = 0.8;
        }
        FollowerResult result;
        result.dir = dir;
        result.baseSpeed = this->baseSpeed;
        result.turnSpeed = this->baseSpeed;
        result.speedFactor = factor;
        result.lastDir = this->lastDir;
        return result;
    }
};