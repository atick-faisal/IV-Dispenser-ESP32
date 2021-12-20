#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>

#include "EspMQTTClient.h"
// #include <ArduinoJson.h>
// #include <PubSubClient.h>

#include "config/config.h"
#include "utils/utils.h"

EspMQTTClient client = EspMQTTClient(
    "WifiSSID",
    "WifiPassword",
    "192.168.1.100",
    "MQTTUsername",
    "MQTTPassword",
    "TestClient");

void onConnectionEstablished() {}

void setup() {
    initializeDebugLog();
}

void loop() {
    debugMessage(INFO, "This is info ...");
    debugMessage(LOADING, "Loading something ... ");
    debugMessage(SUCCESS, "Successfully loaded ...");
    debugMessage(ERROR, "Error occuered!");
    delay(5000);
}