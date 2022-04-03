#ifndef DISPENSER_CONTROL
#define DISPENSER_CONTROL

#include <Arduino.h>

#include "../utils/utils.h"

void setFlowRate(float flowRate);
void handleStepperButton();

#endif