#include <Arduino.h>
#include "common/robot/movement/movement.h"
#include "lineSensor.h"
#include "lineInterpreter.h"
#include "lineMazeLogic.h"
#include "mazeController.h"
#include "common/tools/bluetooth.h"

int sensorPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };

LineSensor sensor(sensorPins, 8, 700);
LineInterpreter interpreter;

MazeLogic maze(RIGHT_FIRST);
MazeController controller( 200, 255);


void setup() {
    Serial.begin(9600);
    setupMotor();
    sensor.setup();
    blueTooth.begin(9600);
}


void loop() {
    LineReading reading = sensor.read();
    LineState state = interpreter.interpret(reading.mask);
    MazeMove move = maze.decide(state);
    MotorCommand cmd = controller.execute(move);
    moveSpeed(cmd.left, cmd.right);
}