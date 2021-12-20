#ifndef UTILS
#define UTILS

#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>

const int SSID_LOCATION = 100;
const int PASS_LOCATION = 200;

struct WiFiCredentials {
    String ssid;
    String pass;
};

// ... MQTT client utils
String getDeviceId();

// ... EEPROM utils
bool isWiFiCredentialsAvailable();
WiFiCredentials getWiFiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);

#endif
