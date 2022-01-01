#include "utils.h"

void initializeWiFi() { WiFi.mode(WIFI_STA); }

bool connectToWiFi(const char* ssid, const char* pass) {
    debugMessage(LOADING, "Connecting to WiFi ... ");
    WiFi.begin(ssid, pass);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        if (millis() > (start + WIFI_CONNECTION_TIMEOUT)) {
            debugMessage(ERROR, "Failed to connect to WiFi!");
            return false;
        }
    }
    debugMessage(SUCCESS, "Connected to WiFi ... ");
    return true;
}