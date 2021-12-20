#ifndef UTILS
#define UTILS

#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>

#include "../config/config.h"

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

// ... Debug utils
void initializeDebugLog();
void debugMessage(DebugLevel debugLevel, const String message);

// ... WiFi utils
bool connectToWiFi(const char* ssid, const char* pass);

// ... MQTT client utils
String getDeviceId();

// ... EEPROM utils
bool isWiFiCredentialsAvailable();
WiFiCredentials getWiFiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);

#endif
