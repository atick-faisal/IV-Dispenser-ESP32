#ifndef DISPENSER_REGISTRATION
#define DISPENSER_REGISTRATION

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

#include "../utils/utils.h"

BluetoothSerial Bluetooth;
StaticJsonDocument<256> registrationRequest;
StaticJsonDocument<16> registrationResponse;

bool registrationMode = true;

void inialializeBluetooth();
void handleBluetoothTrafic();

#endif