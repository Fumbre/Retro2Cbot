/**
 * @name physical maze - PRO VERSION
 * @author Francisco & Uraib
 * @description Timed movement with Active Safety and Right-Hand Rule Priority.
 */

#include "physical_maze.h"

const int FWD_SPEED = 230;
const int TURN_SPEED = 180;

const int TURN_90_MS = 520;
const int TURN_180_MS = 850;
const int FORWARD_TIME_MS = 600;
const int REVERSE_TIME_MS = 600; // Increased to ensure it clears the wall
const int CHECK_PAUSE_MS = 250;

const float WALL_DIST = 16.0;
const float EMERGENCY_STOP_DIST = 10.0;

const float MAX_DIF = 2.0;

float lastF = -1;
float lastR = -1;
float lastL = -1;

enum MazeState
{
    MAZE_FORWARD_TIMED,
    MAZE_CHECK,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_TURN_180,
    MAZE_REVERSE
};

int mazeState = MAZE_FORWARD_TIMED;
static Timer actionTimer;

// The "Snapshots"
float distBeforeMove = -1;

// RS - reflective sensor
ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 200, 25);
Sequence mazeSequence3(&rsLine3);

// maze variables
bool isMazeStarted3 = false;
bool isEndSequence3 = false;
bool mazePassed3 = false;
bool startOnce2 = true;

bool turn180Left = true;

void physicalMazeSetup()
{
    buildHC12Connection();
    setupSonar();
    setupMotor();
    setupGripper();
}

void physicalMaze()
{
    static Timer t;

    // set poisition of robot
    if (!isMazeStarted3)
    {
        if (mazeSequence3.readyToStart(1))
        {
            isMazeStarted3 = true;
        }
        return;
    }

    if (startOnce2)
    {
        moveSpeed(FWD_SPEED, FWD_SPEED);
        startOnce2 = false;
    }

    if (!isEndSequence3)
    {
        if (!mazeSequence3.start(230, 9, 280))
            return;
    }

    if (!isEndSequence3)
    {

        LineState currentStatus = rsLine3.pattern();

        switch (currentStatus)
        {

        case CENTER:
            moveSpeed(FWD_SPEED, FWD_SPEED);
            break;

        case SLIGHT_LEFT:
            moveSpeed(FWD_SPEED * .8, FWD_SPEED);
            break;

        case SLIGHT_RIGHT:
            moveSpeed(FWD_SPEED, FWD_SPEED * .8);
            break;
        case HARD_LEFT:
        {
            moveSpeed(FWD_SPEED * 0, FWD_SPEED);
            break;
        };
        case HARD_RIGHT:
        {
            moveSpeed(FWD_SPEED, FWD_SPEED * 0);
            break;
        };

        case ALL_WHITE:
            solvingPhysicalMaze();
            break;
        case ALL_BLACK:
            isEndSequence3 = mazeSequence3.isDetecetingBlackSquare(80);

            break;
        }
    }

    if (isEndSequence3)
    {
        mazeSequence3.end(&mazePassed3, "BB011");
    }
}
void solvingPhysicalMaze()
{
    switch (mazeState)
    {

    case MAZE_FORWARD_TIMED:
        // Snapshot 1: Right when the state starts
        if (distBeforeMove < 0)
        {
            distBeforeMove = getDistanceCM_Front();
            actionTimer.resetTimeout();
        }

        if (!actionTimer.timeout(FORWARD_TIME_MS))
        {
            float currentF = getDistanceCM_Front();

            // Emergency stop if we get too close
            if (currentF < EMERGENCY_STOP_DIST)
            {
                moveStopAll();
                distBeforeMove = -1;
                mazeState = MAZE_CHECK;
            }
            else
            {
                moveStabilized(FWD_SPEED, FWD_SPEED);
            }
        }
        else
        {
            // TIMER ENDED: Snapshot 2
            moveStopAll();
            float distAfterMove = getDistanceCM_Front();

            // LOGIC: If we traveled less than 4cm in 600ms, we are DEFINITELY stuck.
            // (A healthy robot should move ~15-20cm in this time)
            if (abs(distBeforeMove - distAfterMove) < 4.0 && distAfterMove < 30.0)
            {
                mazeState = MAZE_REVERSE;
            }
            else
            {
                mazeState = MAZE_CHECK;
            }

            distBeforeMove = -1; // Reset for next time
            actionTimer.resetTimeout();
        }
        break;

    case MAZE_CHECK:
    {
        moveStopAll();
        delay(CHECK_PAUSE_MS);
        float r = getDistanceCM_Right();
        float f = getDistanceCM_Front();
        float l = getDistanceCM_Left();

        if (lastF < 0)
        {
            lastF = f;
            lastR = r;
            lastL = l;
        }

        // only reverse if passed grace period
        if (abs(f - lastF) < MAX_DIF && abs(l - lastL) < MAX_DIF && abs(r - lastR) < MAX_DIF)
        {
            actionTimer.resetTimeout();
            mazeState = MAZE_REVERSE;
        }
        else
        {
            // right free
            if (r > WALL_DIST)
            {
                mazeState = MAZE_TURN_RIGHT_90;
            }
            else if (f > WALL_DIST)
            { // front free
                mazeState = MAZE_FORWARD_TIMED;
            }
            else if (l > WALL_DIST)
            { // left free
                mazeState = MAZE_TURN_LEFT_90;
            }
            else
            {
                mazeState = MAZE_TURN_180; // 3 walls
            }
        }

        // update last values
        lastF = f;
        lastL = l;
        lastR = r;

        actionTimer.resetTimeout();
        break;
    }

    case MAZE_REVERSE:
        if (!actionTimer.timeout(REVERSE_TIME_MS))
        {
            moveStabilized(-FWD_SPEED, -FWD_SPEED);
        }
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            // Force a turn so it doesn't just hit the same wall again
            mazeState = MAZE_TURN_LEFT_90;
        }
        break;

    case MAZE_TURN_LEFT_90:
        if (!actionTimer.timeout(TURN_90_MS))
            moveStabilized(-TURN_SPEED, TURN_SPEED);
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_RIGHT_90:
        if (!actionTimer.timeout(TURN_90_MS))
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_FORWARD_TIMED;
        }
        break;

    case MAZE_TURN_180:
        if (!actionTimer.timeout(TURN_180_MS))
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        else
        {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_CHECK;
        }
        break;
    }
}