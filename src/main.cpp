#include "common/constant/robot.h"
#include "common/robot/motor/motor.h"
#include "common/tools/bluetooth.h"
#include "common/robot/movement/movement.h"
#include "common/robot/reflective_sensor/reflective_sensor.h"
#include "common/robot/sonar/sonar.h"
#include <Arduino.h>
#include "common/tools/Timer.h"
#include "common/tools/tests/test_basic_movements/test_basic_movements.h"
#include "common/tools/tests/test_reflective_sensor/test_reflective_sensor.h"
#include "common/tools/tests/test_pulses.h"
#include "common/constant/reflective_sensor.h"
#include "common/robot/neopixel/neopixel.h"
#include "common/robot/movement/movementPID.h"
#include "maps_pogram/maze_line/maze_line.h"
#include "common/robot/hc12/hc12.h"
#include "common/tools/JSON.h"
#include "common/tools/Reflective_sensor.h"
#include "maps_pogram/follow_single_line/follow_single_line.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  buildHC12Connection();
}

unsigned long lastTime = 0;

void loop()
{
  Json json;
  json.add("event","gripper");
  json.add("method","POST");
  Json* list[1];
  Json inside;
  inside.add("gripperStatus",true);
  inside.add("robotCode","BB016");
  list[0] = &inside;
  json.addArray("data",list,1);
  String data =  json.toString();
  unsigned long now = millis();
  if(now - lastTime >= 2000){
    sendDataFromHC12(data);
    lastTime = now;
  }
}