/**
 * @name physical maze
 * @author Francisco
 * @date 11-12-2025
 */

#include "physical_maze.h"

const int FWD_SPEED = 230;
const int TURN_SPEED = 200;

const int TURN_90_MS  = 450;
const int TURN_180_MS = 1000;

const int FORWARD_TIME_MS = 600;   // time to walk
const int CHECK_PAUSE_MS  = 150;   // pause to check

const float WALL_DIST = 15.0;
const float SONAR_MIN = 2.0;

enum MazeState
{
    MAZE_FORWARD_TIMED,
    MAZE_CHECK,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_TURN_180
};

int mazeState = MAZE_FORWARD_TIMED;

static Timer actionTimer;

void physicalMazeSetup()
{
    setupSonar();
    setupMotor();
    setupGripper();
}

void physicalMaze()
{
    solvingPhysicalMaze();
}

void solvingPhysicalMaze()
{
    switch (mazeState)
    {

    // ------------------------------------------
    // go forward for x ms
    case MAZE_FORWARD_TIMED:
        if (!actionTimer.timeout(FORWARD_TIME_MS))
        {
            moveStabilized(FWD_SPEED, FWD_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_CHECK;
        }
        break;

    // ------------------------------------------
    // check
    case MAZE_CHECK:
    {
        delay(CHECK_PAUSE_MS);

        // right sonar
        float r = getDistanceCM_Right();
        bool wallRight = (r >= SONAR_MIN && r <= WALL_DIST);

        if (!wallRight)
        {
            mazeState = MAZE_TURN_RIGHT_90;
            actionTimer.resetTimeout();
            break;
        }

        // front one
        float f = getDistanceCM_Front();
        bool wallFront = (f >= SONAR_MIN && f <= WALL_DIST);

        // left one
        float l = getDistanceCM_Left();
        bool wallLeft = (l >= SONAR_MIN && l <= WALL_DIST);

        // decision
        if (wallFront && wallLeft && wallRight) {
            mazeState = MAZE_TURN_180;
        }
        else if (wallFront && wallRight) {
            mazeState = MAZE_TURN_LEFT_90;
        }
        else {
            mazeState = MAZE_FORWARD_TIMED;
        }

        actionTimer.resetTimeout();
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
            mazeState = MAZE_FORWARD_TIMED;
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
            mazeState = MAZE_FORWARD_TIMED;
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
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;
    }
}
