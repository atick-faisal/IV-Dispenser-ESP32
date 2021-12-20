#ifndef CONFIG
#define CONFIG

#include <Arduino.h>

#define DEBUG

const String BLUETOOTH_NAME = "I/V Dispenser";

const char* BROKER_IP = "broker.emqx.io";
const char* BROKER_USER = "admin";
const char* BROKER_PASS = "admin";
const short PORT = 1883;

// ... Global variables
EspMQTTClient client;
bool registrationMode = true;

#endif