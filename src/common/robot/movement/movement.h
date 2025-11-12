/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 */
#pragma once
#include <Arduino.h>
#include "common/constant/Robot.h"

void moveForward(int speed);

void moveBackward(int speed);

void switchDirection(int leftSpeed, int rightSpeed);

void stopMotors();

int getPWMvalue(int speed);

void initWheelsPin();

float getLeftFactor(int speed);

float getRightFactor(int speed);

void rotate180(int speed, String direction);
