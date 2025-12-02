
#include "common/tools/bluetooth.h"
#include "maps_pogram/follow_single_line/follow_single_line.h"

const int SETTING_MODE = 2;

void setup()
{
  Serial.begin(9600);
  blueTooth.begin(9600);
  initFollowLiner();
}

void loop()
{
  running();
}