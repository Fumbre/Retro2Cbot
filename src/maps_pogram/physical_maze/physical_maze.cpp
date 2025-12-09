#include "physical_maze.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"

// functions to turn
void turnLeft90() {
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
    return (f < 17);  // true = is wall
}

bool doubleCheckRight() {
    moveSpeed(150, 150);
    delay(100);
    moveStopAll();
    delay(30);

    int r = getDistanceCM_Right();
    return (r < 17);
}

void mazeInit() {}

void mazeStep() {

    static bool gripperClosed = false;

    if (!gripperClosed) {
        for (int i = 0; i < 50; i++) {          // 1 second of pulses
            gripper(1000);                      // 1200 = closed (adjust if needed)
            delay(20);
        }
        gripperClosed = true;
    }

    // first check
    bool front = isObstacleFront(17);
    bool right = isObstacleRight(17);

    // no wall
    if (!front && !right) {
        moveStabilized(200, 200);
        return;
    }

    // just wall in right
    if (!front && right) {

        int currentRightDist = getDistanceCM_Right();
        int ideal = 17;
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
        turnLeft90();
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
