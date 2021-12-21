#ifndef DISPENSER_REGISTRATION
#define DISPENSER_REGISTRATION

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

#include "../utils/utils.h"

extern StaticJsonDocument<256> registrationRequest;
extern StaticJsonDocument<16> registrationResponse;

extern bool registrationMode;

// void inialializeBluetooth();
void handleBluetoothTrafic();

#endif