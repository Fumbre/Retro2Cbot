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
extern int colorArray[4][3];
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

extern String RSSendDataStatus;

extern int* RS_SEND_DATA_RAW_ARRAY[8];
//=================================================================================

//================================ sonar ==========================================
extern float sonarSendDatafrontDistance;
extern float sonarSendDataRightDistance;
extern float sonarSendDataLeftDistance;
//=================================================================================