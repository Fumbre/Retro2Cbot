#include "physical_maze.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"

// functions to turn
void turnLeft90() {
    moveSpeed(-200, 200);
    delay(260);
    moveStopAll();
    delay(50);
}

void turnLeft90_both() {
    moveSpeed(-200, 200);
    delay(260);
    moveStopAll();
    delay(50);
}

void turnRight180() {
    moveSpeed(200, -200);
    delay(520);
    moveStopAll();
    delay(50);
}

// double check 
bool doubleCheckFront() {

    moveSpeed(150, 150);
    delay(100);   // go ~3–5 cm
    moveStopAll();
    delay(30);

    // another check
    int f = getDistanceCM_Front();
    return (f < 25);  // true = is wall
}

bool doubleCheckRight() {
    moveSpeed(150, 150);
    delay(100);
    moveStopAll();
    delay(30);

    int r = getDistanceCM_Right();
    return (r < 25);
}

void mazeInit() {}

void mazeStep() {

    // first check
    bool front = isObstacleFront(25);
    bool right = isObstacleRight(25);

    // no wall
    if (!front && !right) {
        moveStabilized(200, 200);
        return;
    }

    // just wall in right
    if (!front && right) {

        int currentRightDist = getDistanceCM_Right();
        int ideal = 15;
        int margin = 1;

        if (currentRightDist < ideal - margin) {     // very close
            moveStabilized(170, 200);               // go left
            return;
        }

        moveStabilized(200, 200);
        return;
    }

    // wall
    moveStopAll();
    delay(5);

    // double check
    if (front) {
        front  = doubleCheckFront();
    }
    
    if (right) {
        right  = doubleCheckRight();
    }
    
    //  front = 0 right = 0 >> no wall
    if (!front && !right) {
        moveStabilized(200, 200);
        return;
    }

    // both detected >> turn left
    if (front && right) {
        turnLeft90_both();
        return;
    }

    // just front >> turn left
    if (front && !right) {
        turnLeft90();

        // check again
        if (doubleCheckFront()) {
            // wall >> 180º right
            turnRight180();
        }
        return;
    }
}
