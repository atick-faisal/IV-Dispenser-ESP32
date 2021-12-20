#include "utils.h"

WiFiCredentials getWiFiCredentials() {
    WiFiCredentials credentials;
    credentials.ssid = EEPROM.readString(SSID_LOCATION);
    credentials.pass = EEPROM.readString(PASS_LOCATION);
    return credentials;
}

bool isWiFiCredentialsAvailable() {
    WiFiCredentials credentials = getWiFiCredentials();
    return (credentials.ssid.length() > 0) && (credentials.pass.length() > 0);
}