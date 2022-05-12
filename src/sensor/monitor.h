#ifndef DISPENSER_MONITOR
#define DISPENSER_MONITOR

#include <Arduino.h>

#include "../utils/utils.h"
#include "control.h"
#include <HX711.h>
#include <RunningMedian.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void monitorDispenserState();
void monitorUrineOutput();
void sendDispenserState();
void lcdTemplate();
void lcdClearVal();

#endif