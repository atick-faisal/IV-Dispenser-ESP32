#include "utils.h"

WiFiCredentials credentials;

void initializeEEPROM() {
    if (EEPROM.begin(EEPROM_SIZE)) {
        debugMessage(SUCCESS, "EEPROM initiated ... ");
    } else {
        debugMessage(ERROR, "EEPROM Failed!");
    }
}

void updateWiFiCredentials() {
    debugMessage(LOADING, "Looking for credentials ... ");
    credentials.room = EEPROM.readString(ROOM_LOCATION);
    credentials.ssid = EEPROM.readString(SSID_LOCATION);
    credentials.pass = EEPROM.readString(PASS_LOCATION);
    debugMessage(INFO, credentials.room);
    debugMessage(INFO, credentials.ssid);
    debugMessage(INFO, credentials.pass);
}

bool isWiFiCredentialsAvailable() {
    updateWiFiCredentials();
    bool credentialsFound =
        (credentials.ssid.length() > 0) && (credentials.pass.length() > 0);
    if (credentialsFound) {
        debugMessage(SUCCESS, "Credenials found ... ");
    } else {
        debugMessage(ERROR, "Credenials not found!");
    }

    return credentialsFound;
}

void saveWiFiCredentials(WiFiCredentials credentials) {
    debugMessage(LOADING, "Saving credentials ... ");
    EEPROM.writeString(ROOM_LOCATION, credentials.room);
    EEPROM.writeString(SSID_LOCATION, credentials.ssid);
    EEPROM.writeString(PASS_LOCATION, credentials.pass);
    EEPROM.commit();
    debugMessage(SUCCESS, "Successfully saved credentials ... ");
}