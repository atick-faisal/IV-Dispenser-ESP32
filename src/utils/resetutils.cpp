#include "utils.h"

extern bool registrationMode;
extern bool mqttConnected;

void handleReset() {
    if (digitalRead(RESET_PIN) == HIGH) {
        unsigned long start = millis();
        debugMessage(LOADING, "Hold on to reset the device in 5 secs ... ");
        while (digitalRead(RESET_PIN) == HIGH) {
            if (millis() > start + RESET_TIMEOUT) {
                clearWiFiCredentials();
                registrationMode = true;
                mqttConnected = false;
                debugMessage(SUCCESS, "Reset complete ... ");
                debugMessage(INFO, "Restrating device ... ");
                ESP.restart();
                return;
            }
            delay(100);  // ... for debouncing
        }
        debugMessage(ERROR, "Reset failed!");
    }
}