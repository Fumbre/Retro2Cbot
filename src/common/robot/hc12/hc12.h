#pragma once
#include "common/constant/hc12.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

void buildHC12Connection();

void sendDataFromHC12(String data);
