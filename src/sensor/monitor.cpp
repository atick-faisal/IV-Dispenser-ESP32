#include "monitor.h"

void monitorDispenserState() {
    // ... TDDO: Implement this

    float flowRate = (float)random(0, 100);
    float dripRate = (float)random(20, 120);
    float urineOut = (float)random(0, 1000);

    setFlowRate(flowRate);

    String alertMessage = "";

    publishData(flowRate, dripRate, urineOut, alertMessage);
}