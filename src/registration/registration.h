#ifndef REGISTRATION
#define REGISTRATION

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

#include "../config/config.h"
#include "../utils/utils.h"

BluetoothSerial Bluetooth;

StaticJsonDocument<256> registrationRequest;
StaticJsonDocument<16> registrationResponse;

void inialializeBluetooth();
void handleBluetoothTrafic();

#endif