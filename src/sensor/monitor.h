#ifndef DISPENSER_MONITOR
#define DISPENSER_MONITOR

#include <Arduino.h>

#include "../utils/utils.h"
#include "control.h"

void monitorDispenserState();
void sendDispenserState();

#endif