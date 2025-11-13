#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

// Controla LEDs integrados (usam os mesmos pinos dos motores)
void initLEDs();
void setLEDsMoving();
void setLEDsStopped();
