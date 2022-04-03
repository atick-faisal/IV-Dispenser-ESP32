#include "control.h"

int16_t position = 0;

void rotateCCW(uint16_t steps) {
    position += steps;
    if (position > 1400) position = 1400;
    digitalWrite(DIR_PIN, LOW);
    for (uint16_t x = 0; x < steps; x++) {
        digitalWrite(STEP_PIN, HIGH);
        delay(2);
        digitalWrite(STEP_PIN, LOW);
        delay(2);
    }
    debugMessage(INFO, "Current Position: " + String(position));
}

void rotateCW(uint16_t steps) {
    position -= steps;
    if (position < 0) position = 0;
    digitalWrite(DIR_PIN, HIGH);
    for (uint16_t x = 0; x < steps; x++) {
        digitalWrite(STEP_PIN, HIGH);
        delay(2);
        digitalWrite(STEP_PIN, LOW);
        delay(2);
    }
    debugMessage(INFO, "Current Position: " + String(position));
}

void handleStepperButton() {
    while (!digitalRead(BUTTON_CCW))
    {
        debugMessage(INFO, "CCW Button Pressed!");
        rotateCCW(1);
        delay(10);
    }

    while (!digitalRead(BUTTON_CW))
    {
        debugMessage(INFO, "CW Button Pressed!");
        rotateCW(1);
        delay(10);
    }
}

void setFlowRate(float flowRate) {
    uint16_t moveStep = (uint16_t)(flowRate * 1400);

    if (position < moveStep) {
        while (position < moveStep) {
            rotateCCW(1);
        }
    } else if (position > moveStep) {
        while (position > moveStep) {
            rotateCW(1);
        }
    }

    debugMessage(INFO, String(position) + "," + String(moveStep) + "," + String(flowRate));
}