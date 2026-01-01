#pragma once
#include <Arduino.h>
// ============================== motor pulses count ===============================
extern volatile long motor_left_pulses_counter;
extern volatile long motor_right_pulses_counter;
// =================================================================================

// ============================== gripper ==========================================
extern bool gripperStatus;
//==================================================================================

// ============================== neopixels ========================================
extern int Red0;
extern int Green0;
extern int Blue0;

extern int Red1;
extern int Green1;
extern int Blue1;

extern int Red2;
extern int Green2;
extern int Blue2;

extern int Red3;
extern int Green3;
extern int Blue3;
//==================================================================================

//================================ reflective sensor ===============================
extern int a0;
extern int a1;
extern int a2;
extern int a3;
extern int a4;
extern int a5;
extern int a6;
extern int a7;

extern String status;
//=================================================================================

//================================ sonar ==========================================
extern float frontDistance;
extern float leftDistance;
extern float rigthDistance;
//=================================================================================