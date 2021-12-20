#include "utils.h"

String getDeviceId() {
    return "IVD_" + WiFi.macAddress();
}

EspMQTTClient getMqttClient() {
    WiFiCredentials credentials = getWiFiCredentials();
    return EspMQTTClient(
        credentials.ssid.c_str(),
        credentials.pass.c_str(),
        BROKER_IP,
        BROKER_USER,
        BROKER_PASS,
        getDeviceId().c_str(),
        PORT
    );
}

void onConnectionEstablished() {}