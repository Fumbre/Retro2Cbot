/**
 * @name physical maze
 * @author Francisco
 * @date 11-12-2025
 */

#include "physical_maze.h"

// --- TUNING ---
const int OBST_LIMIT_CM = 18;
const int SIDE_LIMIT_CM = 20;

const int FWD_SPEED  = 170;
const int TURN_SPEED = 200;
const int TURN_90_MS = 420;   // Adjust this for a perfect 90 degree turn
const int PAUSE_MS   = 200;   // How long to wait for sensors to "settle"

// RS - reflective sensor
ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint3(&rsLine3);

// variable to send data to next robot when maze is passed
bool mazePassed3 = false;

// end sequence variable
bool isEndSequence3 = false;

bool mazeStarted = false;

float slightConf3 = 0.8;
int baseSpeed3    = 180;

enum MazeState {
    MAZE_FORWARD,
    MAZE_STOP_AND_WAIT,
    MAZE_DC_READ,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_POST_TURN_PAUSE
};

int mazeState = MAZE_FORWARD;
static Timer actionTimer;   // One timer to rule them all

// sonar filtering
float lastValidLeft  = 30.0;
float lastValidRight = 30.0;

void physicalMazeSetup() {
    setupSonar();
    setupMotor();
    setupGripper();
}

void physicalMaze() {
    static Timer t;
    static Timer t1;

    // set position of robot
    if (t.executeOnce(0)) {
        entryPoint3.onPossition(1);   // this is first robot so it will go immediately
    }

    if (!isEndSequence3 && !mazeStarted) {
        if (!entryPoint3.pickUp()) {
            return;
        }

        // pickUp terminou >> iniciar maze corretamente
        mazeStarted = true;
        mazeState   = MAZE_FORWARD;
        actionTimer.resetTimeout();
    }

    // if it's not end of sequence do it
    if (!isEndSequence3) {

        LineState currentStatus = rsLine3.pattern();
        // todo include HARD _LEFT and _RIGHT to put robot in the center of line!!

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

                // main physicalMaze code
                switch (mazeState) {

                    case MAZE_FORWARD: {
                        // reading distances
                        float distF = getDistanceCM_Front();
                        float distL = getDistanceCM_Left();
                        float distR = getDistanceCM_Right();

                        // FRONT obstacle detection
                        if (distF > 1.0 && distF < OBST_LIMIT_CM) {
                            moveStopAll();
                            actionTimer.resetTimeout();
                            mazeState = MAZE_STOP_AND_WAIT;
                            return;
                        }

                        // SIDE correction
                        if (distL > 1.0 && distL < SIDE_LIMIT_CM) {
                            moveStabilized(120, 240);   // steer right
                        }
                        else if (distR > 1.0 && distR < SIDE_LIMIT_CM) {
                            moveStabilized(240, 120);   // steer left
                        }
                        else {
                            moveStabilized(FWD_SPEED, FWD_SPEED);
                        }
                        break;
                    }

                    case MAZE_STOP_AND_WAIT:
                        if (actionTimer.timeout(PAUSE_MS)) {
                            mazeState = MAZE_DC_READ;
                        }
                        break;

                    case MAZE_DC_READ: {
                        float l = getDistanceCM_Left();
                        float r = getDistanceCM_Right();

                        bool validL = (l > 1.0 && l < 100.0);
                        bool validR = (r > 1.0 && r < 100.0);

                        // filtering
                        if (validL) {
                            lastValidLeft = l;
                        }
                        else {
                            l = lastValidLeft;
                        }

                        if (validR) {
                            lastValidRight = r;
                        }
                        else {
                            r = lastValidRight;
                        }

                        actionTimer.resetTimeout();

                        // decision logic
                        if (!validL && validR) {
                            mazeState = MAZE_TURN_RIGHT_90;
                        }
                        else if (validL && !validR) {
                            mazeState = MAZE_TURN_LEFT_90;
                        }
                        else if (validL && validR) {
                            if (l < r) {
                                mazeState = MAZE_TURN_RIGHT_90;
                            }
                            else {
                                mazeState = MAZE_TURN_LEFT_90;
                            }
                        }
                        else {
                            mazeState = MAZE_TURN_LEFT_90;
                        }
                        break;
                    }

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

                    case MAZE_POST_TURN_PAUSE:
                        if (actionTimer.timeout(PAUSE_MS)) {
                            mazeState = MAZE_FORWARD;
                        }
                        break;
                }
                break;
        }
    }
    else {
        // this is end of sequence (black square)
        if (t1.timeout(500)) {
            gripperUnCatch();
        }

        if (!t.timeout(1000)) {
            moveStabilized(-215, -215);
        }
        else {
            stopMotors();
        }
    }
}
