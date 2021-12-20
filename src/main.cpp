#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>

#define DEBUG

#include "EspMQTTClient.h"
// #include <ArduinoJson.h>
// #include <PubSubClient.h>

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
    Serial.begin(115200);
}

void loop() {
    Serial.println(isWiFiCredentialsAvailable());
    delay(10000);
}