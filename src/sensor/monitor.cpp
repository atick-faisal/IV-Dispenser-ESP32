#include "monitor.h"

// ... Drip Detector
bool dripFlag = false;
uint8_t dripCount = 0;
uint16_t elapsedTime = 0;
float currentVal = 0.0;
unsigned long initTime = millis();

// ... Load Cell
float scale_val = 0;

HX711 scale;
RunningMedian samples = RunningMedian(20);

float flowRate = (float)random(0, 100);
float dripRate = (float)random(20, 120);
float urineOut = (float)random(0, 1000);

String alertMessage = "";

float adaptiveThreshold = 0.0;
float movingAvg = 0.0;
float oldMovingAvg = 0.0;

void monitorDispenserState() {
    currentVal = (float)pow(
        (float)analogRead(SENSE_PIN) / 4096.0, 2);

    if (currentVal < DRIPPING_THRESHOLD && !dripFlag) {
        elapsedTime += millis() - initTime;
        initTime = millis();
        dripFlag = true;
        dripCount++;

    } else if (currentVal > DRIPPING_THRESHOLD && dripFlag) {
        if ((millis() - initTime) > DRIP_WIDTH_TOLERANCE) {
            dripFlag = false;
            if (dripCount == N_DRIP) {
                dripRate = N_DRIP * 60000.0 / (float)elapsedTime;
                flowRate = dripRate * 3;
                elapsedTime = 0;
                dripCount = 0;
            }
        }
    }

    if (currentVal > DRIPPING_THRESHOLD) {
        movingAvg = ADAPTIVE_TH_ALPHA * currentVal +
                    (1 - ADAPTIVE_TH_ALPHA) * oldMovingAvg;
        adaptiveThreshold = movingAvg - 0.03;
        oldMovingAvg = movingAvg;
    }

    // debugMessage(INFO, "[ " + String(currentVal) + " ]" +
    //                        " Threshold: " + String(adaptiveThreshold) +
    //                        " Drip Count: " + String(dripCount) +
    //                        " Drip Rate: " + String(dripRate) +
    //                        " Flow Rate: " + String(flowRate));

    // setFlowRate(flowRate);
}

void monitorUrineOutput() {
    samples.add(scale.get_units());
    urineOut = samples.getAverage();
    debugMessage(INFO, "Urine Output: " + String(urineOut));
}

void sendDispenserState() {
    publishData(
        flowRate,
        dripRate,
        urineOut,
        alertMessage);
}