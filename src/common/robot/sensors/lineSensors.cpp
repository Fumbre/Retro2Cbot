#include "common/robot/sensors/lineSensors.h"

void setupSensors()
{
    pinMode(LINE_SENSOR_D8, OUTPUT);
    pinMode(LINE_SENSOR_D7, OUTPUT);
    pinMode(LINE_SENSOR_D6, OUTPUT);
    pinMode(LINE_SENSOR_D5, OUTPUT);
    pinMode(LINE_SENSOR_D4, OUTPUT);
    pinMode(LINE_SENSOR_D3, OUTPUT);
    pinMode(LINE_SENSOR_D2, OUTPUT);
    pinMode(LINE_SENSOR_D1, OUTPUT);
}
