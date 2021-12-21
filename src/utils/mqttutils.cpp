#include "utils.h"

StaticJsonDocument<STATUS_BUFFER_LEN> dispenserStatus;
StaticJsonDocument<COMMAND_BUFFER_LEN> command;

bool mqttConnected = false;
String deviceId;

extern WiFiCredentials credentials;

String getDeviceId() {
    return "2332"; // + WiFi.macAddress();
}

void _configureWillMessage(String deviceId, String room) {
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room_number"] = room;
    dispenserStatus["drip_rate"] = 0.0;
    dispenserStatus["flow_rate"] = 0.0;
    dispenserStatus["urine_out"] = 0.0;
    dispenserStatus["alert_message"] = "Device disconnected";
}

EspMQTTClient getMqttClient() {
    char willMessage[STATUS_BUFFER_LEN];
    deviceId = getDeviceId();
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
    _client.setKeepAlive(MQTT_KEEP_ALIVE);
    _client.enableLastWillMessage(
        PUBLISH_TOPIC.c_str(),
        willMessage,
        true);

    return _client;
}

void publishData(
    float flowRate,
    float dripRate,
    float urineOut,
    String alertMessage
) {
    debugMessage(LOADING, "Publishing states ... ");
    // WiFiCredentials credentials = getWiFiCredentials();
    // String room = credentials.room;
    // String deviceId = getDeviceId();
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room_number"] = credentials.room;
    dispenserStatus["drip_rate"] = dripRate;
    dispenserStatus["flow_rate"] = flowRate;
    dispenserStatus["urine_out"] = urineOut;
    dispenserStatus["alert_message"] = "Device disconnected";
    char statusBuffer[STATUS_BUFFER_LEN];
    serializeJson(dispenserStatus, statusBuffer);
    client.publish(PUBLISH_TOPIC, statusBuffer);
    debugMessage(SUCCESS, "Successfully published ... ");
}

void onConnectionEstablished() {
    debugMessage(SUCCESS, "MQTT connected ... ");
    mqttConnected = true;
    String subscribeTopic = SUBSCRIBE_TOPIC + getDeviceId();
    client.subscribe(subscribeTopic.c_str(), [](const String& payload) {
        debugMessage(INFO, payload);
        DeserializationError error = deserializeJson(command, payload);
        if (error) {
            debugMessage(ERROR, "Json parsing failed!");
        } else {
            setFlowRate((float)command["flow_rate"]);
        }
    }, MQTT_QOS);
}