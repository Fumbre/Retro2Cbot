/**
 * @name physical maze - PRO VERSION
 * @author Francisco & Uraib
 * @description Timed movement with Active Safety and Right-Hand Rule Priority.
 */

#include "physical_maze.h"

// --- CONSTANTS ---
const int FWD_SPEED = 230;
const int TURN_SPEED = 200;

const int TURN_90_MS = 450;
const int TURN_180_MS = 1000;

const int FORWARD_TIME_MS = 600;
const int CHECK_PAUSE_MS = 150;

const float WALL_DIST = 18.0; // Slightly increased for safety
const float SONAR_MIN = 2.0;
const float EMERGENCY_STOP_DIST = 10.0; // Stop immediately if front wall is this close

ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 220, 35);
Sequence mazeSequence3(&rsLine3);

// maze varialbes
bool isMazeStarted3 = false;
bool isEndSequence3 = false;
bool mazePassed3 = false;

float slightConf3 = 0.75;
int baseSpeed3 = 160;

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
    //     if (!mazeSequence3.start(255, 10))
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

    solvingPhysicalMaze();
}

void solvingPhysicalMaze()
{
    switch (mazeState)
    {
    // --- STEP 1: MOVE FORWARD WITH SAFETY ---
    case MAZE_FORWARD_TIMED:
        if (!actionTimer.timeout(FORWARD_TIME_MS))
        {
            // SAFETY CHECK: While moving, make sure we aren't about to hit a wall
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

    // --- STEP 2: DECIDE WHERE TO GO (Right-Hand Rule) ---
    case MAZE_CHECK:
    {
        delay(CHECK_PAUSE_MS); // Let sensors settle

        float r = getDistanceCM_Right();
        float f = getDistanceCM_Front();
        float l = getDistanceCM_Left();

        // 1. Right is open? TURN RIGHT (Priority 1)
        if (r > WALL_DIST)
        {
            mazeState = MAZE_TURN_RIGHT_90;
        }
        // 2. Front is open? GO FORWARD (Priority 2)
        else if (f > WALL_DIST)
        {
            mazeState = MAZE_FORWARD_TIMED;
        }
        // 3. Left is open? TURN LEFT (Priority 3)
        else if (l > WALL_DIST)
        {
            mazeState = MAZE_TURN_LEFT_90;
        }
        // 4. Stuck? TURN 180
        else
        {
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
        if (didMoveLeft(TURN_SPEED, 22))
        {
            mazeState = MAZE_FORWARD_TIMED;
            resetMoveLeft();
        }
        else
        {
            mazeState = MAZE_TURN_180;
        }
        break;
    }
}