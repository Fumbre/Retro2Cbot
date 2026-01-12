/**
 * @name physical maze
 * @author Francisco
 * @date 11-12-2025
*/

#include "physical_maze.h"

// turning
const int OBST_LIMIT_CM = 15;
const int SIDE_LIMIT_CM = 15;

const int FWD_SPEED = 150;
const int TURN_SPEED = 200;
const int TURN_90_MS = 420;
const int TURN_180_MS = 840;
const int PAUSE_MS = 200;

// start sequence
ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 220, 35);
Sequence mazeSequence3(&rsLine3);

// maze varialbes
bool isMazeStarted3 = false;
bool isEndSequence3 = false;
bool mazePassed3 = false;

bool wallFront = false;

float slightConf3 = 0.75;
int baseSpeed3 = 160;

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

void physicalMaze()
{
    solvingPhysicalMaze();
    // static Timer t;

    // // set poisition of robot
    // if (!isMazeStarted3)
    // {
    //     if (mazeSequence3.readyToStart(3))
    //     {
    //         isMazeStarted3 = true;
    //     }
    //     return;
    // }

    // if (t.executeOnce(0))
    // {
    //     moveSpeed(230, 230);
    // }

    // if (!isEndSequence3)
    // {
    //     if (!mazeSequence3.start(255))
    //         return;
    // }

    // if (!isEndSequence3)
    // {

    //     LineState currentStatus = rsLine3.pattern();

    //     switch (currentStatus)
    //     {

    //     case CENTER:
    //         moveSpeed(baseSpeed3, baseSpeed3);
    //         break;

    //     case SLIGHT_LEFT:
    //         moveSpeed(baseSpeed3 * slightConf3, baseSpeed3);
    //         break;

    //     case SLIGHT_RIGHT:
    //         moveSpeed(baseSpeed3, baseSpeed3 * slightConf3);
    //         break;

    //     case ALL_WHITE:
    //         solvingPhysicalMaze();
    //         break;
    //     case ALL_BLACK:
    //         isEndSequence3 = mazeSequence3.isDetecetingBlackSquare(62);

    //         break;
    //     }
    // }

    // if (isEndSequence3)
    // {
    //     mazeSequence3.end(&mazePassed3, "BB011");
    // }
}

void solvingPhysicalMaze()
{

    switch (mazeState)
    {

    // ------------------------------------------
    case MAZE_FORWARD:
    {
        float distF = getDistanceCM_Front();

            if (distF > 2.0 && distF < OBST_LIMIT_CM) {
                moveStopAll();
                actionTimer.resetTimeout();
                mazeState = MAZE_STOP_AND_WAIT;
            }
            else {
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
            break;
        }

    // ------------------------------------------
    case MAZE_STOP_AND_WAIT:
        if (actionTimer.timeout(PAUSE_MS))
        {
            mazeState = MAZE_DECIDE;
        }
        break;

        // ------------------------------------------
        case MAZE_DECIDE: {
            
            float f = getDistanceCM_Front();
            float l = getDistanceCM_Left();
            float r = getDistanceCM_Right();

            bool wallFront = (f > 2.0 && f < OBST_LIMIT_CM);
            bool wallLeft  = (l > 2.0 && l < SIDE_LIMIT_CM);
            bool wallRight = (r > 2.0 && r < SIDE_LIMIT_CM);

        actionTimer.resetTimeout();

            // 3 walls
            if (wallLeft && wallRight && wallFront) {
                mazeState = MAZE_TURN_180;
            }
            // only wall in front
            else if (wallFront && !wallLeft && !wallRight) {
                if (l > r) {
                    mazeState = MAZE_TURN_LEFT_90;
                } else {
                    mazeState = MAZE_TURN_RIGHT_90;
                }
            }
            // left free
            else if (!wallLeft && wallFront && wallRight) {
                mazeState = MAZE_TURN_LEFT_90;
            }
            // right free
            else if (wallLeft && wallFront && !wallRight) {
                mazeState = MAZE_TURN_RIGHT_90;
            }
            break;
        }

    // ------------------------------------------
    case MAZE_TURN_LEFT_90:
        if (!actionTimer.timeout(TURN_90_MS))
        {
            moveStabilized(-TURN_SPEED, TURN_SPEED); // try to see how didMoveLeft works
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    // ------------------------------------------
    case MAZE_TURN_RIGHT_90:
        if (!actionTimer.timeout(TURN_90_MS))
        {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    // ------------------------------------------
    case MAZE_TURN_180:
        if (!actionTimer.timeout(TURN_180_MS))
        {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    // ------------------------------------------
    case MAZE_POST_TURN_PAUSE:
        if (actionTimer.timeout(PAUSE_MS))
        {
            mazeState = MAZE_FORWARD;
        }
        break;
    }
}
