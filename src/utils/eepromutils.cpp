#include "utils.h"

WiFiCredentials getWiFiCredentials() {
    debugMessage(LOADING, "Looking for credentials ... ");
    WiFiCredentials credentials;
    credentials.room = EEPROM.readString(ROOM_LOCATION);
    credentials.ssid = EEPROM.readString(SSID_LOCATION);
    credentials.pass = EEPROM.readString(PASS_LOCATION);
    return credentials;
}

bool isWiFiCredentialsAvailable() {
    WiFiCredentials credentials = getWiFiCredentials();
    return (credentials.ssid.length() > 0) && (credentials.pass.length() > 0);
}

void saveWiFiCredentials(WiFiCredentials credentials) {
    debugMessage(LOADING, "Saving credentials ... ");
    EEPROM.writeString(ROOM_LOCATION, credentials.room);
    EEPROM.writeString(SSID_LOCATION, credentials.ssid);
    EEPROM.writeString(PASS_LOCATION, credentials.pass);
    debugMessage(SUCCESS, "Successfully saved credentials ... ");
}