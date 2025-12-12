#include "physical_maze.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"
#include "common/tools/Timer.h"

const int OBST_LIMIT_CM     = 20;     
const int FWD_SPEED         = 225;    
const int TURN_SPEED        = 200;    
const int CORRECTION_SPEED  = 180;                  // small re-ajusts
const unsigned long TURN_90_MS = 450;
const unsigned long DC_MOVE_MS = 120;

enum MazeState {
    MAZE_FORWARD,
    MAZE_DC_MOVE,
    MAZE_DC_READ,
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90
};

static MazeState mazeState = MAZE_FORWARD;

static Timer dcTimer;
static Timer turnTimer;

static bool dcRight = false;
static bool dcLeft  = false;

void mazeInit() {
    mazeState = MAZE_FORWARD;
    dcTimer.hardReset();
    turnTimer.hardReset();
}

void mazeStep() {

    gripper(1200);

    switch (mazeState) {

        // forward
        case MAZE_FORWARD: {

            bool front = isObstacleFront(OBST_LIMIT_CM);
            bool right = isObstacleRight(OBST_LIMIT_CM);
            bool left  = isObstacleLeft(OBST_LIMIT_CM);

            // wall in front >> start double-check
            if (front) {
                moveStopAll();
                dcTimer.resetTimeout();
                mazeState = MAZE_DC_MOVE;
                return;
            }

            // wall left and right >> go forward
            if (right && left) {
                moveStabilized(FWD_SPEED, FWD_SPEED);
                return;
            }
            
            // wall right >> go forward
            if (right && !left) {
                moveStabilized(CORRECTION_SPEED, FWD_SPEED);
                return;
            }
            
            // wall left >> go forward
            if (left && !right) {
                moveStabilized(FWD_SPEED, CORRECTION_SPEED);
                return;
            }

            moveStabilized(FWD_SPEED, FWD_SPEED);
            return;
        }

        // double-check move
        case MAZE_DC_MOVE: {

            // if dc's time hasn't ended yet, keep moving forward 
            if (!dcTimer.timeout(DC_MOVE_MS)) {
                moveStabilized(FWD_SPEED * 0.5, FWD_SPEED * 0.5);
                return;
            }

            // DC_MOVE completed >> stop and proceed to read confirmation.
            moveStopAll();
            dcTimer.resetTimeout();
            mazeState = MAZE_DC_READ;
            return;
        }

        // side sonares only
        case MAZE_DC_READ: {

            dcRight = isObstacleRight(OBST_LIMIT_CM);
            dcLeft  = isObstacleLeft(OBST_LIMIT_CM);

            float distR = getDistanceCM_Right();
            float distL = getDistanceCM_Left();

            turnTimer.resetTimeout();

            // choose the side with more space
            if (distR > distL) {
                mazeState = MAZE_TURN_RIGHT_90;
            } else {
                mazeState = MAZE_TURN_LEFT_90;
            }
            return;
        }

        // 90º left
        case MAZE_TURN_LEFT_90: {

            // if the turning point hasn't ended yet, keep turning
            if (!turnTimer.timeout(TURN_90_MS)) {
                moveStabilized(-TURN_SPEED, TURN_SPEED);
                return;
            }

            moveStopAll();
            mazeState = MAZE_FORWARD;
            return;
        }

        // 90º right
        case MAZE_TURN_RIGHT_90: {

            // if the turning point hasn't ended yet, keep turning
            if (!turnTimer.timeout(TURN_90_MS)) {
                moveStabilized(TURN_SPEED, -TURN_SPEED);
                return;
            }

            moveStopAll();
            mazeState = MAZE_FORWARD;
            return;
        }
    }
}
