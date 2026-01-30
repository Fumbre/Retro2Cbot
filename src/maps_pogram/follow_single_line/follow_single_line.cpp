/**
 * @name follow_single_line
 * @authors Fumbre (Vladyslav) & Aria & Sunny
 * @date 15-12-2025
 * @details Controls the robot to follow a single line maze using reflective sensors and sonar.
 * @details Includes obstacle avoidance, maze sequence handling, LED feedback, and motor control.
*/

#include "follow_single_line.h"

ReflectiveSensor rsLine(PINS_RS, PINS_RS_LENGTH, 220, 35);
Sequence mazeSequence(&rsLine);

// Maze state variables
bool mazePassed = false;
bool isEndSequence = false;
bool isMazeStarted = false;
bool safeZone = true;

// Movement configuration
int fullSpeed = 255;
float slightConf = 0.8;         // speed multiplier for slight turns
float hardConf = -0.5;          // speed multiplier for hard turns

static Timer t;

/**
 * @name followLine
 * @authors Fumbre (Vladyslav) & Aria & Sunny
 * @date 15-12-2025
 * @details Main loop for following a single line in a maze.
 * @details Handles maze start, reflective sensor reading, obstacle avoidance, motor control, and maze completion.
*/

void followLine() {
    if (!isMazeStarted) {
        if (mazeSequence.readyToStart(1)) {
            isMazeStarted = true;
        }
        return;
    }

    if (t.executeOnce(0)) {
        moveSpeed(230, 230);
    }

    LineState currnetPattern = rsLine.pattern();

    if (!isEndSequence) {
        dataSend();

        if (!mazeSequence.start(255, 8, 180))
            return;
    }

    if (!isEndSequence) {
        if (!avoiding) {
            if (t.interval(35, 75)) {
                float distance = getDistanceCM_Front();

                if (safeZone && distance <= 13 && distance >= 2) {
                    safeZone = false;
                    obstacleAvoidance(255);
                    return;
                }

                if (distance > 13) {
                    safeZone = true;
                }
            }
        } else {
            obstacleAvoidance(255);
            return;
        }

        solvingFollowSingleLine(currnetPattern, fullSpeed, slightConf, hardConf);
    }

    if (isEndSequence) {
        if (!t.timeout(1000)) {
            dataSend();
        }
        mazeSequence.end(&mazePassed, "BB016");
    }
}

/**
 * @name solvingFollowSingleLine
 * @authors Fumbre (Vladyslav) & Aria & Sunny
 * @date 15-12-2025
 * @param currnetPattern Current reflective sensor pattern
 * @param fullSpeed Base motor speed
 * @param slightConf Multiplier for slight turns
 * @param hardConf Multiplier for hard turns
 * @details Implements the core logic for following the line based on the current sensor pattern.
 * @details Controls motor speed adjustments and LED feedback according to pattern.
*/

void solvingFollowSingleLine(LineState currnetPattern, int fullSpeed, float slightConf, float hardConf) {
    switch (currnetPattern) {
    case CENTER:
        moveSpeed(fullSpeed, fullSpeed);
        turnOnAllLeds(0, 255, 0);
        break;

    case SLIGHT_LEFT:
        moveSpeed(fullSpeed * slightConf, fullSpeed);
        break;

    case SLIGHT_RIGHT:
        moveSpeed(fullSpeed, fullSpeed * slightConf);
        break;

    case HARD_LEFT:
        moveSpeed(fullSpeed * hardConf, fullSpeed);
        turnOnSomeLeds((int[]){3, 0}, 2, 255, 255, 0);
        turnOnSomeLeds((int[]){1, 2}, 2, 0, 255, 0);
        break;

    case HARD_RIGHT:
        moveSpeed(fullSpeed, fullSpeed * hardConf);
        turnOnSomeLeds((int[]){1, 2}, 2, 255, 255, 0);
        turnOnSomeLeds((int[]){3, 0}, 2, 0, 255, 0);
        break;

    case ALL_BLACK:
        isEndSequence = mazeSequence.isDetecetingBlackSquare(80);
        moveSpeed(fullSpeed, fullSpeed);
        break;
    }
}

/**
 * @name followLineSetup
 * @authors Fumbre (Vladyslav)
 * @date 15-12-2025
 * @details Initializes all components required for following a line maze.
 * @details Sets up HC12 communication, motors, gripper, sonar, and reflective sensors.
*/

void followLineSetup() {
    buildHC12Connection();
    setupMotor();
    setupGripper();
    gripperUnCatch();
    setupSonar();
    rsLine.setup();
}
