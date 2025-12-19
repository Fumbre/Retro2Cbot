#include "physical_maze.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"
#include "common/tools/Timer.h"

// --- TUNING ---
const int OBST_LIMIT_CM   = 18;      
const int FWD_SPEED       = 225;     
const int TURN_SPEED      = 200;     
const int TURN_90_MS      = 450;  // Adjust this for a perfect 90 degree turn
const int PAUSE_MS        = 200;  // How long to wait for sensors to "settle"

enum MazeState { 
    MAZE_FORWARD, 
    MAZE_STOP_AND_WAIT, 
    MAZE_DC_READ, 
    MAZE_TURN_LEFT_90, 
    MAZE_TURN_RIGHT_90,
    MAZE_POST_TURN_PAUSE 
};

int mazeState = MAZE_FORWARD; 

static Timer actionTimer; // One timer to rule them all

void mazeInit() {
    mazeState = MAZE_FORWARD;
    actionTimer.hardReset();
}

void mazeStep() {
    gripper(1200);

    switch (mazeState) {
        case MAZE_FORWARD: {
            float distF = getDistanceCM_Front();
            float distL = getDistanceCM_Left();
            float distR = getDistanceCM_Right();

            // 1. FRONT CHECK
            if (distF < OBST_LIMIT_CM && distF > 1.0) {
                moveStopAll();
                actionTimer.resetTimeout(); // Start timer for the pause
                mazeState = MAZE_STOP_AND_WAIT;
                return;
            }

            // 2. SIDE STEERING (Keeping it centered)
            if (distL < 10.0 && distL > 1.0) {
                moveSpeed(140, 240); // Steer Right
            } 
            else if (distR < 10.0 && distR > 1.0) {
                moveSpeed(240, 140); // Steer Left
            } 
            else {
                moveSpeed(FWD_SPEED, FWD_SPEED); 
            }
            break;
        }

        case MAZE_STOP_AND_WAIT:
            // Wait for physical vibration to stop before reading sensors
            if (actionTimer.timeout(PAUSE_MS)) {
                mazeState = MAZE_DC_READ;
            }
            break;

        case MAZE_DC_READ: {
            float l = getDistanceCM_Left();
            float r = getDistanceCM_Right();
            
            actionTimer.resetTimeout(); // Reset for the actual turn duration
            
            // Decide direction based on where there is more space
            if (l < r) {
                mazeState = MAZE_TURN_RIGHT_90;
            } else {
                mazeState = MAZE_TURN_LEFT_90;
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

        case MAZE_POST_TURN_PAUSE:
            // Crucial: Wait so the Forward logic doesn't freak out 
            // seeing the wall it just turned away from.
            if (actionTimer.timeout(PAUSE_MS)) {
                mazeState = MAZE_FORWARD;
            }
            break;
    }
}