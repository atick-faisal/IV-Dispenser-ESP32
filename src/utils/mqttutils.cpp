#include "utils.h"

StaticJsonDocument<STATUS_BUFFER_LEN> dispenserStatus;
StaticJsonDocument<COMMAND_BUFFER_LEN> command;

bool mqttConnected = false;
String deviceId;

extern WiFiCredentials credentials;
extern EspMQTTClient client;

String getDeviceId() {
    return "IVD_" + WiFi.macAddress();
}

void _configureWillMessage(String deviceId, String room) {
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room"] = room;
    dispenserStatus["drip_rate"] = 0.0;
    dispenserStatus["flow_rate"] = 0.0;
    dispenserStatus["urine_out"] = 0.0;
    dispenserStatus["alert_message"] = "Device disconnected";
}

void configureMqttClient() {
    updateWiFiCredentials();
    char willMessage[STATUS_BUFFER_LEN];
    deviceId = getDeviceId();
    _configureWillMessage(deviceId, credentials.room);
    serializeJson(dispenserStatus, willMessage);
    client.setWifiCredentials(
        credentials.ssid.c_str(),
        credentials.pass.c_str());
    client.setMqttServer(BROKER_IP.c_str());
    client.setMqttClientName(deviceId.c_str());

#ifdef DEBUG
    client.enableDebuggingMessages();
#endif
    // client.enableHTTPWebUpdater();
    // client.enableOTA();
    client.setKeepAlive(MQTT_KEEP_ALIVE);
    client.enableLastWillMessage(
        PUBLISH_TOPIC.c_str(),
        willMessage,
        true);
}

void publishData(
    float flowRate,
    float dripRate,
    float urineOut,
    String alertMessage) {
    debugMessage(LOADING, "Publishing states ... ");
    String topic = PUBLISH_TOPIC + deviceId;
    // WiFiCredentials credentials = getWiFiCredentials();
    // String room = credentials.room;
    // String deviceId = getDeviceId();
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room"] = credentials.room;
    dispenserStatus["drip_rate"] = dripRate;
    dispenserStatus["flow_rate"] = flowRate;
    dispenserStatus["urine_out"] = urineOut;
    dispenserStatus["alert_message"] = "";
    char statusBuffer[STATUS_BUFFER_LEN];
    serializeJson(dispenserStatus, statusBuffer);
    client.publish(topic, statusBuffer);
    debugMessage(SUCCESS, "Successfully published ... ");
}

void onConnectionEstablished() {
    debugMessage(SUCCESS, "MQTT connected ... ");
    mqttConnected = true;
    String subscribeTopic = SUBSCRIBE_TOPIC + getDeviceId();
    client.subscribe(
        subscribeTopic.c_str(), [](const String& payload) {
            debugMessage(INFO, payload);
            DeserializationError error = deserializeJson(command, payload);
            if (error) {
                debugMessage(ERROR, "Json parsing failed!");
            } else {
                setFlowRate((float)command["flow_rate"]);
            }
        },
        MQTT_QOS);
}