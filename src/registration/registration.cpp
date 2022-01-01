#include "registration.h"

BluetoothSerial Bluetooth;
EspMQTTClient client;

StaticJsonDocument<256> registrationRequest;
StaticJsonDocument<24> registrationResponse;

bool registrationMode = true;

void inialializeBluetooth() {
    debugMessage(LOADING, "Starting bluetooth ... ");
    Bluetooth.begin(BLUETOOTH_NAME);
    debugMessage(SUCCESS, "Bluetooth initialized ... ");
}

void _initiateMqtt() {
    debugMessage(LOADING, "Starting MQTT ... ");
    configureMqttClient();
    registrationMode = false;
}

void _sendRegistrationResponse(bool status) {
    debugMessage(LOADING, "Sending registration response ... ");
    char buffer[24];
    registrationResponse["success"] = status;
    serializeJson(registrationResponse, buffer);
    Bluetooth.println(buffer);
    debugMessage(SUCCESS, "Response sent ... ");
}

void _registerDevice() {
    debugMessage(LOADING, "Registering device ... ");
    String room = registrationRequest["room_number"];
    String ssid = registrationRequest["wifi_name"];
    String pass = registrationRequest["wifi_password"];
    if (connectToWiFi(ssid.c_str(), pass.c_str())) {
        debugMessage(SUCCESS, "Registration successful ... ");
        _sendRegistrationResponse(true);
        WiFiCredentials credentials;
        credentials.room = room;
        credentials.ssid = ssid;
        credentials.pass = pass;
        saveWiFiCredentials(credentials);

        // ... stop bluetooth
        delay(PAUSE_AFTER_REGISTRATION);
        btStop();

        _initiateMqtt();
    } else {
        debugMessage(ERROR, "Registration failed!");
        _sendRegistrationResponse(false);
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
        DeserializationError error =
            deserializeJson(registrationRequest, incomingData);
        if (error) {
            debugMessage(ERROR, "Error parsing json ... ");
        } else {
            _registerDevice();
        }
    }
}