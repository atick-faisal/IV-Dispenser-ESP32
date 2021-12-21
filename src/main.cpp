#include <Arduino.h>

#include "registration/registration.h"
#include "utils/utils.h"
#include "sensor/monitor.h"

// ... Global variables
extern EspMQTTClient client;
extern bool registrationMode;

unsigned long looper = millis();

void setup() {
    initializeDebugLog();
    inialializeBluetooth();
    initializeWiFi();
    registrationMode = !isWiFiCredentialsAvailable();
    if (!registrationMode) {
        client = getMqttClient();
    }
}

void loop() {
    if (registrationMode) {
        handleBluetoothTrafic();
    } else {
        if (millis() > looper + REFRESH_INTERVAL) {
            looper = millis();
            monitorDispenserState();
        }
        client.loop();
    }
}