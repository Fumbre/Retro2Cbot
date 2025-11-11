/**
 * @name the basic functions of robots
 * @authors Sunny & Nicolo
 */
#pragma once

void moveForward(int speed);

void moveBackward(int speed); 

void switchDirection(int leftSpeed ,int rightSpeed);

void stopMotors();

int getPWMvalue(int speed);

void initWheelsPin();




