#ifndef DISPENSER_MONITOR
#define DISPENSER_MONITOR

#include <Arduino.h>

#include "../utils/utils.h"
#include "control.h"
#include <HX711.h>
#include <RunningMedian.h>

void monitorDispenserState();
void monitorUrineOutput();
void sendDispenserState();

#endif