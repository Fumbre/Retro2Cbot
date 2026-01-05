#include "globalVariable.h"
// ============================== motor pulses count ===============================
volatile long motor_left_pulses_counter = 0;
volatile long motor_right_pulses_counter = 0;
// =================================================================================

// ============================== gripper ==========================================
bool gripperStatus = false;
//==================================================================================

// ============================== neopixels ========================================
int Red0 = 0;
int Green0 = 0;
int Blue0 = 0;

int Red1 = 0;
int Green1 = 0;
int Blue1 = 0;

int Red2 = 0;
int Green2 = 0;
int Blue2 = 0;

int RedR3 = 0;
int Green3 = 0;
int Blue3 = 0;
//==================================================================================

//================================ reflective sensor ===============================
int a0 = 0;
int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;
int a6 = 0;
int a7 = 0;

int* RS_SEND_DATA_RAW_ARRAY[8] = {&a0,&a1,&a2,&a3,&a4,&a5,&a6,&a7};

String RSSendDataStatus = "00000000";
//=================================================================================

//================================ sonar ==========================================
float sonarSendDatafrontDistance = 0.0;
float sonarSendDataLeftDistance = 0.0;
float sonarSendDataRightDistance = 0.0;
//=================================================================================