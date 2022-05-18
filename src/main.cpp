#include <Arduino.h>

#include "registration/registration.h"
#include "sensor/monitor.h"
#include "sensor/control.h"
#include "utils/utils.h"

// ... Global variables
extern EspMQTTClient client;
extern bool registrationMode;
extern bool mqttConnected;
extern float currentVal;
extern float drippingThreshold;
extern float thresholdBuffer;
extern HX711 scale;
extern LiquidCrystal_I2C lcd;

unsigned long looper1 = millis();
unsigned long looper2 = millis();

void setup() {
    pinMode(RESET_PIN, INPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(BUTTON_CCW, INPUT);
    pinMode(BUTTON_CW, INPUT);

    scale.begin(SCALE_DOUT, SCALE_SCK);
    scale.set_scale(CALIBRATION_FACTOR);
    scale.tare();

    lcd.init();
    lcd.backlight();
    lcd.clear();
    delay(200);
    lcdTemplate();

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

    // Threshold calibration (N/A differential value method)
    // for (uint8_t i = 0; i < 50; i++)
    // {
    //     currentVal = (float)analogRead(SENSE_PIN) / 4096.0;
    //     thresholdBuffer += currentVal * currentVal;
    // }
    // drippingThreshold = (thresholdBuffer / 50.0) - 0.02;
}

void loop() {
    if (registrationMode) {
        handleBluetoothTrafic();
    } else {
        client.loop();
        if (mqttConnected) {
            if (millis() > looper1 + REFRESH_INTERVAL) {
                looper1 = millis();
                sendDispenserState();
            }
        }
        handleReset();
        handleStepperButton();
        monitorDispenserState();
        if (millis() > looper2 + REFRESH_INTERVAL/2) {
            looper2 = millis();
            monitorUrineOutput();
        }
    }
}
