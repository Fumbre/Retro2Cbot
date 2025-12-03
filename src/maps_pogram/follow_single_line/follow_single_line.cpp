#include "follow_single_line.h"

void initFollowLiner(){
    setupMotor();
    initNeopixelPins();
    initReflectiveSensor();
}

void running(int speed){
    FollowerResult result = lineFollow(speed);
    switch (result.dir) {
        case CENTER:
            moveSpeed(result.baseSpeed, result.baseSpeed);
            break;

        case SLIGHT_LEFT:
            moveSpeed(result.baseSpeed * result.speedFactor, result.baseSpeed);
            break;

        case SLIGHT_RIGHT:
            moveSpeed(result.baseSpeed, result.baseSpeed * result.speedFactor);
            break;

        case HARD_LEFT:
            moveSpeed(-result.turnSpeed, result.turnSpeed);
            break;

        case HARD_RIGHT:
            moveSpeed(result.turnSpeed, -result.turnSpeed);
            break;

        case LOST:
            // check last direction
            if(result.lastDir == SLIGHT_LEFT || result.lastDir == HARD_LEFT){
                moveSpeed(-result.turnSpeed, result.turnSpeed);
            }else if(result.lastDir == SLIGHT_RIGHT || result.lastDir == HARD_RIGHT){
                moveSpeed(result.turnSpeed,-result.baseSpeed);
            }
    }
}