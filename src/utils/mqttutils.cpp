#include "utils.h"

String getDeviceId() {
    return "IVD_" + WiFi.macAddress();
}

void _configureWillMessage(String deviceId, String room) {
    dispenserStatus.clear();
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room_number"] = room;
    dispenserStatus["drip_rate"] = 0;
    dispenserStatus["flow_rate"] = 0;
    dispenserStatus["urine_out"] = 0;
    dispenserStatus["alert_message"] = "Device disconnected";
}

EspMQTTClient getMqttClient() {
    char willMessage[STATUS_BUFFER_LEN];
    String deviceId = getDeviceId();
    WiFiCredentials credentials = getWiFiCredentials();
    _configureWillMessage(deviceId, credentials.room);
    serializeJson(dispenserStatus, willMessage);
    EspMQTTClient _client = EspMQTTClient(
        credentials.ssid.c_str(),
        credentials.pass.c_str(),
        BROKER_IP.c_str(),
        BROKER_USER.c_str(),
        BROKER_PASS.c_str(),
        deviceId.c_str(),
        PORT);

#ifdef DEBUG
    _client.enableDebuggingMessages();
#endif
    // _client.enableHTTPWebUpdater();
    // _client.enableOTA();
    _client.enableLastWillMessage(
        PUBLISH_TOPIC.c_str(),
        willMessage,
        true);

    return _client;
}

void onConnectionEstablished() {
    debugMessage(SUCCESS, "MQTT connected ... ");
    String subscribeTopic = SUBSCRIBE_TOPIC + getDeviceId();
    client.subscribe(subscribeTopic.c_str(), [](const String& payload) {
        debugMessage(INFO, payload);
        DeserializationError error = deserializeJson(command, payload);
        if (error) {
            debugMessage(ERROR, "Json parsing failed!");
        } else {
            setFlowRate((float)command["flow_rate"]);
        }
    });
}