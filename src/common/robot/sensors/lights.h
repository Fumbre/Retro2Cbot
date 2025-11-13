#pragma once
#include <Arduino.h>
#include "../../constant/Robot.h"

// Controla LEDs integrados (usam pinos dos motores)
void initLEDs();
void setLEDsMoving();
void setLEDsStopped();
