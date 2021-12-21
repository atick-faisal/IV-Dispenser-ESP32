#ifndef DISPENSER_UTILS
#define DISPENSER_UTILS

#include <Arduino.h>
#include <EEPROM.h>
#include <EspMQTTClient.h>
#include <WiFi.h>

#include "../config/config.h"
#include "../sensor/control.h"

const int ROOM_LOCATION = 128;
const int SSID_LOCATION = 160;
const int PASS_LOCATION = 192;
const int WIFI_CONNECTION_TIMEOUT = 30000;

enum DebugLevel {
    INFO,
    SUCCESS,
    LOADING,
    ERROR
};

struct WiFiCredentials {
    String room;
    String ssid;
    String pass;
};

extern EspMQTTClient client;

// ... Logging utils
void initializeDebugLog();
void debugMessage(DebugLevel debugLevel, const String message);

// ... WiFi utils
void initializeWiFi();
bool connectToWiFi(const char* ssid, const char* pass);

// ... MQTT client utils
String getDeviceId();
EspMQTTClient getMqttClient();
void publishData(
    float flowRate,
    float dripRate,
    float urineOut,
    String alertMessage
);

// ... EEPROM utils
bool isWiFiCredentialsAvailable();
WiFiCredentials getWiFiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);

#endif
