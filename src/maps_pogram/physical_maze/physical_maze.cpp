#include "physical_maze.h"
#include "common/robot/movement/movement.h"
#include "common/robot/sonar/sonar.h"
#include "common/robot/gripper/gripper.h"
#include "common/tools/Timer.h"

const int OBST_LIMIT_CM  = 17;              
const int FWD_SPEED      = 170;             // forward speed
const int TURN_SPEED     = 170;             // rotation speed

const unsigned long TURN_90_MS  = 300;      // time for 90º
const unsigned long TURN_180_MS = 600;      // time for 180º
const unsigned long DC_MOVE_MS  = 120;      // time for double-check

enum MazeState {
    MAZE_FORWARD,        
    MAZE_DC_MOVE,                           // DC = Double-check
    MAZE_DC_READ,        
    MAZE_TURN_LEFT_90,
    MAZE_TURN_RIGHT_90,
    MAZE_TURN_180
};

static MazeState mazeState = MAZE_FORWARD;

static Timer dcTimer;
static Timer turnTimer;

// results after double-check
static bool dcFront = false;
static bool dcRight = false;
static bool dcLeft  = false;

void mazeInit() {
    mazeState = MAZE_FORWARD;
    dcTimer.hardReset();
    turnTimer.hardReset();
}

void mazeStep() {

    // always close
    gripper(1200);

    switch (mazeState) {
        
        //move forward
        case MAZE_FORWARD: {
            bool front = isObstacleFront(OBST_LIMIT_CM);
            bool right = isObstacleRight(OBST_LIMIT_CM);
            bool left  = isObstacleLeft(OBST_LIMIT_CM);

            // if wall in front
            if (front) {
                moveStopAll();                          
                dcTimer.resetTimeout();                 
                mazeState = MAZE_DC_MOVE;
                return;
            }   

            // wall on left and right
            if (right && left && !front) {
                moveStabilized(200, 200);
                return;
            }

            // wall right
            if (right && !left) {
                moveStabilized(170, 200);   
                return;
            }

            // wall left
            if (left && !right) {
                moveStabilized(200, 170);
                return;
            }

            // no wall
            moveStabilized(FWD_SPEED, FWD_SPEED);
            return;
        }

        // Double-check move 
        case MAZE_DC_MOVE: {

            // during DC_MOVE, the robot moves slowly
            if (!dcTimer.timeout(DC_MOVE_MS)) {
                moveStabilized(200, 200);
                return;
            }

            // time's up >> pause and proceed to confirmed reading
            moveStopAll();
            dcTimer.resetTimeout();
            mazeState = MAZE_DC_READ;
            return;
        }

        case MAZE_DC_READ: {
        
            // double-check
            dcFront = isObstacleFront(OBST_LIMIT_CM);
            dcRight = isObstacleRight(OBST_LIMIT_CM);
            dcLeft  = isObstacleLeft(OBST_LIMIT_CM);

            // if no wall, keep going
            if (!dcFront && !dcRight && !dcLeft) {
                mazeState = MAZE_FORWARD;
                return;
            }

            // wall front and left >> turn right
            if (dcFront && dcLeft && !dcRight) {
                turnTimer.resetTimeout();
                mazeState = MAZE_TURN_RIGHT_90;
                return;
            }

            // wall front and right >> turn left
            if (dcFront && dcRight && !dcLeft) {
                turnTimer.resetTimeout();
                mazeState = MAZE_TURN_LEFT_90;
                return;
            }

            // wall right and left >> go forward
            if (!dcFront && dcRight && dcLeft) {
                mazeState = MAZE_FORWARD;   
                return;
            }

            // wall everywhere >> do 180º
            if (dcFront && dcRight && dcLeft) {
                turnTimer.resetTimeout();
                mazeState = MAZE_TURN_180;
                return;
            }

            // wall in front >> choose the best side
            if (dcFront && !dcRight && !dcLeft) {

                float rightDistance = getDistanceCM_Right();
                float leftDistance = getDistanceCM_Left();

                turnTimer.resetTimeout();

                if (rightDistance > leftDistance) {
                    mazeState = MAZE_TURN_RIGHT_90;
                } else {
                    mazeState = MAZE_TURN_LEFT_90;
                }
                return;
            }
            mazeState = MAZE_FORWARD;
            return;
        }

        // do 90º to left
        case MAZE_TURN_LEFT_90: {
            if (!turnTimer.timeout(TURN_90_MS)) {
                moveStabilized(-TURN_SPEED, TURN_SPEED);
                return;
            }

            moveStopAll();
            turnTimer.resetTimeout();
            mazeState = MAZE_FORWARD;
            return;
        }

        // do 90º to right
        case MAZE_TURN_RIGHT_90: {
            if (!turnTimer.timeout(TURN_90_MS)) {
                moveStabilized(TURN_SPEED, -TURN_SPEED);
                return;
            }

            moveStopAll();
            turnTimer.resetTimeout();
            mazeState = MAZE_FORWARD;
            return;
        }

        // do 180º
        case MAZE_TURN_180: {
            if (!turnTimer.timeout(TURN_180_MS)) {
                moveStabilized(TURN_SPEED, -TURN_SPEED);
                return;
            }

            moveStopAll();
            turnTimer.resetTimeout();
            mazeState = MAZE_FORWARD;
            return;
        }
    }
}
