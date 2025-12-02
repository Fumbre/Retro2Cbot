#include "reflective_sensor.h"


LineSensor lineSensor(PINS_RS,PINS_RS_LENGTH,THRESHOLD);
LineFollower lineFollower(190,250);
LineInterpreter interpreter;


void initReflectiveSensor(){
    lineSensor.setup();
}

FollowerResult lineFollow(){
    return lineFollower.follow(lineSensor,interpreter);
}