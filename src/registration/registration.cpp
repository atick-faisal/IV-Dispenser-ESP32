#include "registration.h"

void inialializeBluetooth() {
    debugMessage(LOADING, "Starting bluetooth ... ");
    Bluetooth.begin(BLUETOOTH_NAME);
    debugMessage(SUCCESS, "Bluetooth initialized ... ");
}

void _initiateMqtt() {
    debugMessage(LOADING, "Starting MQTT ... ");
    client = getMqttClient();
    registrationMode = false;
}

void _registerDevice() {
    debugMessage(LOADING, "Registering device ... ");
    String room = registrationRequest["room"];
    String ssid = registrationRequest["ssid"];
    String pass = registrationRequest["pass"];
    if(connectToWiFi(ssid.c_str(), pass.c_str())) {
        WiFiCredentials credentials;
        credentials.room = room;
        credentials.ssid = ssid;
        credentials.pass = pass;
        saveWiFiCredentials(credentials);
        _initiateMqtt();
    }
}

void handleBluetoothTrafic() {
    if (Bluetooth.available()) {
        debugMessage(LOADING, "Reading from bluetooth ... ");
        String incomingData;
        while (Bluetooth.available() > 0) {
            incomingData += (char)Bluetooth.read();
        }
        debugMessage(SUCCESS, incomingData);
        DeserializationError error = deserializeJson(
            registrationRequest,
            incomingData);
        if (error) {
            debugMessage(ERROR, "Error parsing json ... ");
        } else {
            _registerDevice();
        }
    }
}