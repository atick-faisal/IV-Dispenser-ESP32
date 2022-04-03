#include <Arduino.h>

#include "registration/registration.h"
#include "sensor/monitor.h"
#include "sensor/control.h"
#include "utils/utils.h"

// ... Global variables
extern EspMQTTClient client;
extern bool registrationMode;
extern bool mqttConnected;

extern HX711 scale;
// extern RunningMedian samples = RunningMedian(20);

unsigned long looper = millis();

void setup() {
    pinMode(RESET_PIN, INPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(BUTTON_CCW, INPUT);
    pinMode(BUTTON_CW, INPUT);

    scale.begin(SCALE_DOUT, SCALE_SCK);
    scale.set_scale(CALIBRATION_FACTOR);
    scale.tare();

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
        handleStepperButton();
        monitorDispenserState();
        monitorUrineOutput();
    }
}
