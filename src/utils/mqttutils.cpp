#include "utils.h"

StaticJsonDocument<STATUS_BUFFER_LEN> dispenserStatus;
StaticJsonDocument<COMMAND_BUFFER_LEN> command;

bool mqttConnected = false;
String deviceId;
char willMessage[STATUS_BUFFER_LEN];

extern WiFiCredentials credentials;
extern EspMQTTClient client;

String getDeviceId() { return "IVD_" + WiFi.macAddress(); }

void configureMqttClient() {
    updateWiFiCredentials();
    deviceId = getDeviceId();

    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room"] = credentials.room;
    dispenserStatus["drip_rate"] = 0.0F;
    dispenserStatus["flow_rate"] = 0.0F;
    dispenserStatus["urine_out"] = 0.0F;
    dispenserStatus["alert_message"] = "Device Disconnected";

    serializeJson(dispenserStatus, willMessage);

    client.setWifiCredentials(credentials.ssid.c_str(),
                              credentials.pass.c_str());
    client.setMqttServer(BROKER_IP.c_str(), BROKER_USER.c_str(),
                         BROKER_PASS.c_str(), PORT);
    client.setMqttClientName(deviceId.c_str());
    client.setKeepAlive(MQTT_KEEP_ALIVE);
    client.enableLastWillMessage(PUBLISH_TOPIC.c_str(),
                                 (const char*)willMessage, true);

#ifdef DEBUG
    client.enableDebuggingMessages();
#endif
    // client.enableMQTTPersistence();
    // client.enableHTTPWebUpdater();
    // client.enableOTA();
}

void publishData(float flowRate, float dripRate, float urineOut,
                 String alertMessage) {
    debugMessage(LOADING, "Publishing states ... ");
    String topic = PUBLISH_TOPIC + deviceId;
    dispenserStatus["device_id"] = deviceId;
    dispenserStatus["room"] = credentials.room;
    dispenserStatus["drip_rate"] = dripRate;
    dispenserStatus["flow_rate"] = flowRate;
    dispenserStatus["urine_out"] = urineOut;
    dispenserStatus["alert_message"] = alertMessage;
    char statusBuffer[STATUS_BUFFER_LEN];
    serializeJson(dispenserStatus, statusBuffer);
    client.publish(topic, statusBuffer, true);
    debugMessage(SUCCESS, "Successfully published ... ");
}

void onConnectionEstablished() {
    debugMessage(SUCCESS, "MQTT connected ... ");
    mqttConnected = true;
    String subscribeTopic = SUBSCRIBE_TOPIC + deviceId;
    client.subscribe(
        subscribeTopic.c_str(),
        [](const String& payload) {
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