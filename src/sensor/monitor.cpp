#include "monitor.h"

// ... Drip Detector
bool dripFlag = false;
uint8_t dripCount = 0;
float drippingThreshold = 0.19;
float thresholdBuffer = 0;
uint16_t elapsedTime = 0;
float currentVal;
unsigned long initTime = millis();

// ... Load Cell
float scale_val = 0;

HX711 scale;
RunningMedian weightSamples = RunningMedian(20);
RunningMedian dripSamples = RunningMedian(N_DRIP);

float flowRate = (float)random(0, 100);
float dripRate = (float)random(20, 120);
float urineOut = (float)random(0, 1000);

String alertMessage = "";

float adaptiveThreshold = 0.0;
float movingAvg = 0.0;
float oldMovingAvg = 0.0;

void monitorDispenserState() {
    currentVal = (float)pow((float)analogRead(SENSE_PIN) / 4096.0, 2);
    
    if (currentVal < drippingThreshold && !dripFlag)
    {
        dripSamples.add(millis() - initTime);
        initTime = millis();
        dripFlag = true;
        dripCount++;
    }
    else if (currentVal > drippingThreshold && dripFlag)
    {
        if ((millis() - initTime) > DRIP_WIDTH_TOLERANCE) {
            dripFlag = false;
        }
    }

    dripRate = 60000 / (float)dripSamples.getMedian();
    flowRate = dripRate * 3;

    // if (currentVal > DRIPPING_THRESHOLD) {
    //     movingAvg = ADAPTIVE_TH_ALPHA * currentVal +
    //                 (1 - ADAPTIVE_TH_ALPHA) * oldMovingAvg;
    //     adaptiveThreshold = movingAvg - 0.03;
    //     oldMovingAvg = movingAvg;
    // }

    debugMessage(INFO, "[ " + String(currentVal) + " ]" +
                          " Threshold: " + String(drippingThreshold) +
                          " Drip Count: " + String(dripCount) +
                          " Drip Rate: " + String(dripRate) +
                          " Flow Rate: " + String(flowRate));

    // setFlowRate(flowRate);
}

void monitorUrineOutput() {
    weightSamples.add(scale.get_units());
    urineOut = weightSamples.getAverage();
    // debugMessage(INFO, "Urine Output: " + String(urineOut));
}

void sendDispenserState() {
    publishData(
        flowRate,
        dripRate,
        urineOut,
        alertMessage);
}