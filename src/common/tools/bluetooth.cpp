#include "bluetooth.h"

SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN); // RX, TX

void initBluetooth() {
  BTSerial.begin(9600);     // HC-05 default baud rate
  Serial.println("Bluetooth ready.");
}

void btSend(String message) {
  BTSerial.println(message); // send via Bluetooth
}

bool btAvailable() {
  return BTSerial.available();
}

String btRead() {
  if (BTSerial.available()) {
    return BTSerial.readStringUntil('\n'); // read until newline
  }
  return "";
}
