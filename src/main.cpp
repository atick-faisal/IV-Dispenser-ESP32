#include <Arduino.h>
#include "utils/utils.h"
#include "registration/registration.h"

// ... Global variables
extern EspMQTTClient client;
extern bool registrationMode;

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
        client.loop();
    }
}