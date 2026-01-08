/**
 * @name physical maze
 * @author Francisco
 * @date 11-12-2025
 */

#include "physical_maze.h"

// turning
const int OBST_LIMIT_CM  = 20;   
const int SIDE_LIMIT_CM  = 20;   

const int FWD_SPEED      = 150;
const int TURN_SPEED     = 200;
const int TURN_90_MS     = 420;
const int TURN_180_MS    = 840;
const int PAUSE_MS       = 200;

// start sequence 
ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint3(&rsLine3);

bool mazeStarted = false;
bool inMazeMode  = false;
bool wallFront   = false;

float slightConf3 = 0.75;
int baseSpeed3    = 160;

enum MazeState {
    MAZE_FORWARD,
    MAZE_STOP_AND_WAIT,
    MAZE_DECIDE,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_TURN_180,
    MAZE_POST_TURN_PAUSE
};

int mazeState = MAZE_FORWARD;
static Timer actionTimer;

void physicalMazeSetup() {
    setupSonar();
    setupMotor();
    setupGripper();
}

void physicalMaze() {

    static Timer t;

    // initial position
    if (t.executeOnce(0)) {
        entryPoint3.onPossition(1);
    }

    if (!mazeStarted) {

        LineState currentStatus = rsLine3.pattern();

        switch (currentStatus) {

            case CENTER:
                moveSpeed(baseSpeed3, baseSpeed3);
                break;

            case SLIGHT_LEFT:
                moveSpeed(baseSpeed3 * slightConf3, baseSpeed3);
                break;

            case SLIGHT_RIGHT:
                moveSpeed(baseSpeed3, baseSpeed3 * slightConf3);
                break;

            case ALL_WHITE:
                moveStopAll();

                if (entryPoint3.pickUp()) {
                    mazeStarted = true;
                    inMazeMode  = true;
                    mazeState   = MAZE_FORWARD;
                }
                break;
        }
        return;
    }

    if (!inMazeMode) {
        return;
    }

    switch (mazeState) {

        // ------------------------------------------
        case MAZE_FORWARD: {
            float distF = getDistanceCM_Front();

            if (distF > 1.0 && distF < OBST_LIMIT_CM) {
                wallFront = true;
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_STOP_AND_WAIT;
            }
            else {
                wallFront = false;
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
            break;
        }

        // ------------------------------------------
        case MAZE_STOP_AND_WAIT:
            if (actionTimer.timeout(PAUSE_MS)) {
                mazeState = MAZE_DECIDE;
            }
            break;

        // ------------------------------------------
        case MAZE_DECIDE: {
            float l = getDistanceCM_Left();
            float r = getDistanceCM_Right();

            bool wallLeft  = (l > 1.0 && l < SIDE_LIMIT_CM);
            bool wallRight = (r > 1.0 && r < SIDE_LIMIT_CM);

            actionTimer.resetTimeout();

            // 3 walls
            if (wallLeft && wallRight) {
                mazeState = MAZE_TURN_180;
            }
            // just wall in front
            else if (!wallLeft && !wallRight) {
                if (l > r) {
                    mazeState = MAZE_TURN_LEFT_90;
                } else {
                    mazeState = MAZE_TURN_RIGHT_90;
                }
            }
            // left free
            else if (!wallLeft) {
                mazeState = MAZE_TURN_LEFT_90;
            }
            // right free
            else {
                mazeState = MAZE_TURN_RIGHT_90;
            }
            break;
        }

        // ------------------------------------------
        case MAZE_TURN_LEFT_90:
            if (!actionTimer.timeout(TURN_90_MS)) {
                moveStabilized(-TURN_SPEED, TURN_SPEED);
            }
            else {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_POST_TURN_PAUSE;
            }
            break;

        // ------------------------------------------
        case MAZE_TURN_RIGHT_90:
            if (!actionTimer.timeout(TURN_90_MS)) {
                moveStabilized(TURN_SPEED, -TURN_SPEED);
            }
            else {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_POST_TURN_PAUSE;
            }
            break;

        // ------------------------------------------
        case MAZE_TURN_180:
            if (!actionTimer.timeout(TURN_180_MS)) {
                moveStabilized(TURN_SPEED, -TURN_SPEED);
            }
            else {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_POST_TURN_PAUSE;
            }
            break;

        // ------------------------------------------
        case MAZE_POST_TURN_PAUSE:
            if (actionTimer.timeout(PAUSE_MS)) {
                mazeState = MAZE_FORWARD;
            }
            break;
    }
}
