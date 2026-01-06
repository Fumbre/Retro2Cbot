/**
 * @name physical maze
 * @author Francisco
 * @date 11-12-2025
 */

#include "physical_maze.h"

// --- TUNING ---
const int OBST_LIMIT_CM = 18;
const int FWD_SPEED = 215;
const int TURN_SPEED = 200;
const int TURN_90_MS = 450; // Adjust this for a perfect 90 degree turn
const int PAUSE_MS = 200;   // How long to wait for sensors to "settle"

// RS - reflective sensor
ReflectiveSensor rsLine3(PINS_RS, PINS_RS_LENGTH, 220, 35);
StartSequence entryPoint3(&rsLine3);

// variable to send data to next robot when maze is passed
bool mazePassed3 = false;

// end sequence variable
bool isEndSequence3 = false;

bool mazeStarted = false;

enum MazeState // The map of the minds; making a lsit of names for numbers
{
    MAZE_FORWARD,
    MAZE_STOP_AND_WAIT,
    MAZE_DC_READ,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_POST_TURN_PAUSE
};

int mazeState = MAZE_FORWARD;
static Timer actionTimer; // One timer to rule them all

// sonar filtering
float lastValidLeft  = 30.0;
float lastValidRight = 30.0;

void physicalMazeSetup()
{
    setupMotor();
    setupGripper();
}

void physicalMaze()
{
    static Timer t;
    static Timer t1;
      
    // set poisition of robot
    if (t.executeOnce(0)) {
        entryPoint3.onPossition(1); // this is first robot so it will go immediately
    }

    if (!isEndSequence3 && !mazeStarted) {
    
        if (!entryPoint3.pickUp()) {
            return;
        }
        
        // pickUp terminou >> iniciar maze corretamente
        mazeStarted = true;
        mazeState = MAZE_FORWARD;
        actionTimer.resetTimeout();
    }

    // if it's not end of sequence do it
    if (!isEndSequence3) {

    // main physicalMaze code
    switch (mazeState) {
    case MAZE_FORWARD: {

        // Logic for moving forward and obstacle detection
        // reading distances (through sensors)
        float distF = getDistanceCM_Front();
        float distL = getDistanceCM_Left();
        float distR = getDistanceCM_Right();

        // OBSTACLE DETECTION (FRONT) logic
        if (distF > 1.0 && distF < OBST_LIMIT_CM) {
            moveStopAll();
            actionTimer.resetTimeout();                     // Start timer for the pause
            mazeState = MAZE_STOP_AND_WAIT;                 // Change the robot to waiting stage
            return;
        }

        // SIDE correction
        if (distL > 1.0 && distL < 10.0) {
            moveStabilized(140, 240);                       // steer right
        } else if (distR > 1.0 && distR < 10.0) {
            moveStabilized(240, 140);                       // steer left
        } else {
            moveStabilized(FWD_SPEED, FWD_SPEED);
        }
        break;
    }

    case MAZE_STOP_AND_WAIT:
        // To avoid false readings right after stopping, wait a bit
        // 200 ms pause
        if (actionTimer.timeout(PAUSE_MS)) {
            mazeState = MAZE_DC_READ;
        }
        break;

    case MAZE_DC_READ: {
        // making easy references to left and right distances
        float l = getDistanceCM_Left();
        float r = getDistanceCM_Right();

        bool validL = (l > 1.0);
        bool validR = (l < 1.0);

        // filtering
            if (validL) {
                lastValidLeft = l;
            } else {
                l = lastValidLeft;
            }
                
            if (validR) {
                lastValidRight = r;
            } else {
                r = lastValidRight;
            }
                
        actionTimer.resetTimeout(); // Reset for the actual turn duration

        // decision logic
        if (!validL && validR) {
            mazeState = MAZE_TURN_RIGHT_90;
        } else if (validL && !validR) {                         // Só esquerda válida
            mazeState = MAZE_TURN_LEFT_90;
        } else if (validL && validR) {                          // Ambas válidas
            
            if (l < r) {
                mazeState = MAZE_TURN_RIGHT_90;
            } else {
                mazeState = MAZE_TURN_LEFT_90;
            }
        } else {                                                // Nenhuma válida
            mazeState = MAZE_TURN_LEFT_90;                      // regra fixa de segurança
        }
        break;
    }

    case MAZE_TURN_LEFT_90:
        // Logic for turning left 90 degrees
        // Using timer to control turn duration since sensors can't help here
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveStabilized(-TURN_SPEED, TURN_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    case MAZE_TURN_RIGHT_90:
        // Logic for turning right 90 degrees
        // Using timer to control turn duration since sensors can't help here
        if (!actionTimer.timeout(TURN_90_MS)) {
            moveStabilized(TURN_SPEED, -TURN_SPEED);
        } else {
            moveStopAll();
            actionTimer.resetTimeout();
            mazeState = MAZE_POST_TURN_PAUSE;
        }
        break;

    case MAZE_POST_TURN_PAUSE:
        // Safe exit habibi
        // We wait a bit after turning to avoid immediate obstacle detection
        // Ghost wall avoidance basically
        if (actionTimer.timeout(PAUSE_MS)) {
            mazeState = MAZE_FORWARD;
        }
        break;
    }
    }
  else
  {
    // this is end of sequence (black square)
    if (t1.timeout(500)) // after 500ms uncatch an object
    {
      gripperUnCatch();
    }
    if (!t.timeout(1000)) // go back during 1s
    {
      moveStabilized(215 * -1, 215 * -1);
    }
    else // after 1s stop all motors
    {
      stopMotors();
    }
  }
}

