#ifndef DISPENSER_REGISTRATION
#define DISPENSER_REGISTRATION

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <EspMQTTClient.h>

#include "../utils/utils.h"

void inialializeBluetooth();
void handleBluetoothTrafic();

#endif