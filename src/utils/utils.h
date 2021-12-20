#ifndef DISPENSER_UTILS
#define DISPENSER_UTILS

#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <EspMQTTClient.h>

#include "logger.h"
#include "../config/config.h"
#include "../sensor/control.h"

const int ROOM_LOCATION = 128;
const int SSID_LOCATION = 160;
const int PASS_LOCATION = 192;
const int WIFI_CONNECTION_TIMEOUT = 30000;

struct WiFiCredentials {
    String room;
    String ssid;
    String pass;
};

// ... WiFi utils
void initializeWiFi();
bool connectToWiFi(const char* ssid, const char* pass);

// ... MQTT client utils
String getDeviceId();
EspMQTTClient getMqttClient();

// ... EEPROM utils
bool isWiFiCredentialsAvailable();
WiFiCredentials getWiFiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);

#endif
