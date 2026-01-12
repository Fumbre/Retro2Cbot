/**
 * @name physical maze - TEST MODE
 * @description All start sequences disabled. Runs Maze Logic immediately.
*/

#include "physical_maze.h"

// --- CONSTANTS ---
const int OBST_LIMIT_CM = 20;
const int SIDE_LIMIT_CM = 20;

const int FWD_SPEED = 150;
const int TURN_SPEED = 200;
const int TURN_90_MS = 420;
const int TURN_180_MS = 840;
const int PAUSE_MS = 200;

// --- MAZE VARIABLES ---
enum MazeState
{
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

void physicalMazeSetup()
{
    setupSonar();
    setupMotor();
    setupGripper();
}

// --- SIMPLIFIED MAIN HANDLER ---
void physicalMaze()
{
    // Jump straight to the maze logic
    solvingPhysicalMaze();
}

// --- MAZE SOLVING LOGIC ---
void solvingPhysicalMaze()
{
    switch (mazeState)
    {
    case MAZE_FORWARD:
    {
        float distF = getDistanceCM_Front();
        float distL = getDistanceCM_Left();
        float distR = getDistanceCM_Right();

        // 1. Obstacle Detection (Front)
        if (distF > 2.0 && distF < OBST_LIMIT_CM) 
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_STOP_AND_WAIT;
        }
        else 
        {
            // 2. Centering Logic (The "Nervous System")
            if (distL < 12.0 && distL > 1.0) 
            {
                // Nudge Right
                moveSpeed(FWD_SPEED - 40, FWD_SPEED + 40); 
            }
            else if (distR < 12.0 && distR > 1.0) 
            {
                // Nudge Left
                moveSpeed(FWD_SPEED + 40, FWD_SPEED - 40);
            }
            else 
            {
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
        }
        break;
    }

    case MAZE_STOP_AND_WAIT:
        if (actionTimer.timeout(PAUSE_MS))
        {
            mazeState = MAZE_DECIDE;
        }
        break;

    case MAZE_DECIDE: 
    {
        float l = getDistanceCM_Left();
        float r = getDistanceCM_Right();

        actionTimer.resetTimeout();

        // Right-Hand Rule: Check Right gap, then Left gap
        if (r > SIDE_LIMIT_CM) 
        {
            mazeState = MAZE_TURN_RIGHT_90;
        } 
        else if (l > SIDE_LIMIT_CM) 
        {
            mazeState = MAZE_TURN_LEFT_90;
        } 
        else 
        {
            mazeState = MAZE_TURN_180;
        }
        break;
    }

    case MAZE_TURN_LEFT_90:
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveSpeed(-TURN_SPEED, TURN_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    case MAZE_TURN_RIGHT_90:
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveSpeed(TURN_SPEED, -TURN_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    case MAZE_TURN_180:
        if (!actionTimer.timeout(TURN_180_MS)) {
            moveSpeed(TURN_SPEED, -TURN_SPEED);
        } else {
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
}