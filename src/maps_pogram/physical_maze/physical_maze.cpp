/**
 * @name physical maze - PRO VERSION
 * @author Francisco & Uraib
 * @description Timed movement with Active Safety and Right-Hand Rule Priority.
*/

#include "physical_maze.h"

const int FWD_SPEED = 230;
const int TURN_SPEED = 180;

const int TURN_90_MS = 550;
const int TURN_180_MS = 850;
const int REVERSE_TIME_MS = 500;
const int FORWARD_TIME_MS = 700;

const float WALL_DIST = 16.0;
const float EMERGENCY_STOP_DIST = 10.0;

const float MAX_DIF = 2.0;

enum MazeState {
    MAZE_FORWARD_TIMED,
    MAZE_CHECK,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_TURN_180,
    MAZE_REVERSE
};

int mazeState = MAZE_FORWARD_TIMED;
static Timer actionTimer;

// last sonar values
float lastF = -1; 
float lastL = -1; 
float lastR = -1;

// ignore reverse for a short period after moving forward
unsigned long ignoreReverseUntil = 0;

void physicalMazeSetup() {
    setupSonar();
    setupMotor();
    setupGripper();
}

void physicalMaze() {
    solvingPhysicalMaze();
}

void solvingPhysicalMaze() {
    float f = getDistanceCM_Front();
    float l = getDistanceCM_Left();
    float r = getDistanceCM_Right();

    switch (mazeState) {

    case MAZE_FORWARD_TIMED:
        if (!actionTimer.timeout(FORWARD_TIME_MS)) {
            if (f < EMERGENCY_STOP_DIST) {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_CHECK;
            } else {
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_CHECK;

            // set grace period to ignore reverse right after moving
            ignoreReverseUntil = millis() + 150;
        }
        break;

    case MAZE_CHECK:
        // first check
        if (lastF < 0) {
            lastF = f; 
            lastL = l; 
            lastR = r;
        }

        // only reverse if passed grace period
        if (abs(f - lastF) < MAX_DIF && abs(l - lastL) < MAX_DIF && abs(r - lastR) < MAX_DIF) {
            actionTimer.resetTimeout();
            mazeState = MAZE_REVERSE;
        } else {
            // right free
            if (r > WALL_DIST) {
                mazeState = MAZE_TURN_RIGHT_90;
            } else if (f > WALL_DIST) {                         // front free
                mazeState = MAZE_FORWARD_TIMED;
            } else if (l > WALL_DIST) {                         // left free
                mazeState = MAZE_TURN_LEFT_90;
            } else {
                mazeState = MAZE_TURN_180;                      // 3 walls
            }
        }

        // update last values
        lastF = f; 
        lastL = l; 
        lastR = r;

        actionTimer.resetTimeout();
        break;

    case MAZE_TURN_LEFT_90:
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveStabilized(-TURN_SPEED, TURN_SPEED);
        } else {
            moveStopAll();
            delay(100);
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_RIGHT_90:
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        } else {
            moveStopAll();
            delay(100);
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_180:
        if (!actionTimer.timeout(TURN_180_MS)) {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_CHECK;
        }
        break;

    case MAZE_REVERSE:
        if (!actionTimer.timeout(REVERSE_TIME_MS)) {
            moveStabilized(-FWD_SPEED, -FWD_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_TURN_LEFT_90;
        }
        break;
    }
}

