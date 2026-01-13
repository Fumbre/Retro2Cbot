/**
 * @name physical maze - PRO VERSION
 * @author Francisco & Uraib
 * @description Timed movement with Active Safety and Right-Hand Rule Priority.
 */

#include "physical_maze.h"

const int FWD_SPEED = 230;
const int TURN_SPEED = 210;

const int TURN_90_MS = 450;

const int FORWARD_TIME_MS = 700;
const int CHECK_PAUSE_MS = 200;

const float WALL_DIST = 18.0;
const float SONAR_MIN = 2.0;
const float EMERGENCY_STOP_DIST = 10.0;

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

bool turn180Left = true;

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
    // forward
    case MAZE_FORWARD_TIMED:
        if (!actionTimer.timeout(FORWARD_TIME_MS))
        {
            if (getDistanceCM_Front() < EMERGENCY_STOP_DIST)
            {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_CHECK;
            }
            else
            {
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_CHECK;
        }
        break;

    // check
    case MAZE_CHECK:
    {
        float r = getDistanceCM_Right();
        float f = getDistanceCM_Front();
        float l = getDistanceCM_Left();

        // right
        if (r > WALL_DIST)
        {
            mazeState = MAZE_TURN_RIGHT_90;
        }
        // front
        else if (f > WALL_DIST)
        {
            mazeState = MAZE_FORWARD_TIMED;
        }
        // left
        else if (l > WALL_DIST)
        {
            mazeState = MAZE_TURN_LEFT_90;
        }
        // 3 walls 
        else
        {
            turn180Left = (l > r);
            mazeState = MAZE_TURN_180;
        }

        actionTimer.resetTimeout();
        break;
    }

    case MAZE_TURN_LEFT_90:
        if (!actionTimer.timeout(TURN_90_MS))
        {
            moveStabilized(-TURN_SPEED, TURN_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_RIGHT_90:
        if (!actionTimer.timeout(TURN_90_MS))
        {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_180:
        if (turn180Left)
        {
            if (didMoveLeft(TURN_SPEED, 22))
            {
                resetMoveLeft();
                mazeState = MAZE_FORWARD_TIMED;
            }
        }
        else
        {
            if (didMoveRight(TURN_SPEED, 22))
            {
                resetMoveRight();
                mazeState = MAZE_FORWARD_TIMED;
            }
        }
        break;
    }
}
