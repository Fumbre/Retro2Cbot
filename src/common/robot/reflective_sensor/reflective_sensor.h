/**
 * @name interface of reflective_sensor
 * @author Sunny
 * @date 21-11-2025
 * 
 */
#pragma once
#include <Arduino.h>
#include "common/constant/reflective_sensor.h"

void initReflectiveSensorsPins();

MotorSpeed checkLine(int baseSpeed);