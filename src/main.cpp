#include <Arduino.h>

#include "registration/registration.h"
#include "sensor/monitor.h"
#include "utils/utils.h"

// ... Global variables
extern EspMQTTClient client;
extern bool registrationMode;
extern bool mqttConnected;

unsigned long looper = millis();

void setup() {
    pinMode(RESET_PIN, INPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    initializeDebugLog();
    initializeEEPROM();
    inialializeBluetooth();
    initializeWiFi();
    registrationMode = !isWiFiCredentialsAvailable();
    if (!registrationMode) {
        configureMqttClient();
    } else {
        debugMessage(INFO, "Starting registration process ... ");
    }
}

void loop() {
    if (registrationMode) {
        handleBluetoothTrafic();
    } else {
        client.loop();
        if (mqttConnected) {
            if (millis() > looper + REFRESH_INTERVAL) {
                looper = millis();
                sendDispenserState();
            }
        }
        handleReset();
        monitorDispenserState();
    }
}
