/**
 * @name interface of HC-12
 * @author Sunny
 * @date 15-12-2025
 */
#pragma once
#include "common/constant/hc12.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

extern SoftwareSerial hc12;

void buildHC12Connection();

void sendDataFromHC12(String data);