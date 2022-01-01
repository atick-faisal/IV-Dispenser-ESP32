#ifndef DISPENSER_CONFIG
#define DISPENSER_CONFIG

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <EspMQTTClient.h>

#define DEBUG  // ... comment this in production build

#define RESET_PIN 34
#define EEPROM_SIZE 256

const String BLUETOOTH_NAME = "I/V Dispenser";

const String BROKER_IP = "broker.emqx.io";
const String BROKER_USER = "admin";
const String BROKER_PASS = "admin";
const String PUBLISH_TOPIC = "dev.atick.mqtt/status/";
const String SUBSCRIBE_TOPIC = "dev.atick.mqtt/command/";
const short PORT = 1883;
const uint8_t MQTT_QOS = 1;
const uint16_t MQTT_KEEP_ALIVE = 60;

const short STATUS_BUFFER_LEN = 256;
const short COMMAND_BUFFER_LEN = 64;

const int RESET_TIMEOUT = 5000;
const int WIFI_CONNECTION_TIMEOUT = 30000;
const unsigned long REFRESH_INTERVAL = 10000;

// ... required for sending registration confirmation
const int PAUSE_AFTER_REGISTRATION = 3000;

#endif