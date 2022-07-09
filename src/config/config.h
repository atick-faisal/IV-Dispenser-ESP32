#ifndef DISPENSER_CONFIG
#define DISPENSER_CONFIG

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <EspMQTTClient.h>

#define DEBUG  // ... comment this in production build

#define RESET_PIN 23
#define EEPROM_SIZE 256

static const char BLUETOOTH_NAME[] = "I/V Dispenser";

static const char BROKER_IP = "broker.emqx.io";
// static const char BROKER_IP[] = "192.168.0.110"; //"192.168.31.161";
static const char BROKER_USER[] = "admin";
static const char BROKER_PASS[] = "admin";
static const char PUBLISH_TOPIC[] = "dev.atick.mqtt/status/";
static const char SUBSCRIBE_TOPIC[] = "dev.atick.mqtt/command/";
const short PORT = 1883;
const uint8_t MQTT_QOS = 1;
const uint16_t MQTT_KEEP_ALIVE = 15;
static const char WILL_MESSAGE[] = "{\"alert_message\":\"Device Disconnected\"}";

const short STATUS_BUFFER_LEN = 256;
const short COMMAND_BUFFER_LEN = 128;

const int RESET_TIMEOUT = 5000;
const int WIFI_CONNECTION_TIMEOUT = 30000;
const unsigned long REFRESH_INTERVAL = 10000;

// ... required for sending registration confirmation
const int PAUSE_AFTER_REGISTRATION = 3000;

// ... Sensors
#define SENSE_PIN 34
#define DRIP_WIDTH_TOLERANCE 300
#define ADAPTIVE_TH_ALPHA 0.1
#define N_DRIP 10

// ... Load Cell
#define CALIBRATION_FACTOR 388.59
#define SCALE_DOUT 4
#define SCALE_SCK 2

// ... Stepper
#define BUTTON_CCW 26
#define BUTTON_CW 25
#define DIR_PIN 32
#define STEP_PIN 33
#define TOTAL_STEPS 200
#define MOVE_STEPS 1

#endif