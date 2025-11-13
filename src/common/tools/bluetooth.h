#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

// Define which pins the HC-05 is connected to
const int BT_RX_PIN = 10;  // Arduino receives (connect to HC-05 TX)
const int BT_TX_PIN = 11;  // Arduino transmits (connect to HC-05 RX)

// Initialize SoftwareSerial
extern SoftwareSerial BTSerial;

// Setup function
void initBluetooth();

// Send message via Bluetooth
void btSend(String message);

// Check if data received
bool btAvailable();

// Read received message
String btRead();
