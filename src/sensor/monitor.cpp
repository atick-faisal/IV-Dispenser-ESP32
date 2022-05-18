#include "monitor.h"

// ... Drip Detector
bool dripFlag = false;
uint8_t dripCount = 0;
float drippingThreshold = 0.003;
float thresholdBuffer = 0;
uint16_t elapsedTime = 0;
float currentVal;
float prevVal;
float diffVal;
unsigned long initTime = millis();

// ... Load Cell
float scale_val = 0;

extern int16_t position;

HX711 scale;
RunningMedian weightSamples = RunningMedian(5);
RunningMedian dripSamples = RunningMedian(N_DRIP);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float flowRate = (float)random(0, 100);
float dripRate = (float)random(20, 120);
float urineOut = (float)random(0, 1000);

String alertMessage = "";

float adaptiveThreshold = 0.0;
float movingAvg = 0.0;
float oldMovingAvg = 0.0;

void monitorDispenserState() {
    // Dripping value calculation for differential value method

    // Read Data
    currentVal = ((float)analogRead(SENSE_PIN) / 4096.0);
    diffVal = currentVal - prevVal;
    diffVal = diffVal * diffVal;
    prevVal = currentVal;
    // Check for drip start
    if (diffVal < drippingThreshold && !dripFlag)
    {
        dripSamples.add(millis() - initTime);
        initTime = millis();
        dripFlag = true;
        dripCount++;
    }
    // Check for drip end
    else if (diffVal > drippingThreshold && dripFlag)
    {
        if ((millis() - initTime) > DRIP_WIDTH_TOLERANCE)
        {
            dripFlag = false;
        }
    }

    // Dripping value calculation for direct value method

    // // Read data
    // currentVal = (float)pow((float)analogRead(SENSE_PIN) / 4096.0, 2);
    // // Check for drip start
    // if (currentVal < drippingThreshold && !dripFlag)
    // {
    //     dripSamples.add(millis() - initTime);
    //     initTime = millis();
    //     dripFlag = true;
    //     dripCount++;
    // }
    // // Check for drip end
    // else if (currentVal > drippingThreshold && dripFlag)
    // {
    //     if ((millis() - initTime) > DRIP_WIDTH_TOLERANCE)
    //     {
    //         dripFlag = false;
    //     }
    // }

    // Calculate drip rate and flow rate
    dripRate = 60000 / (float)dripSamples.getMedian();
    flowRate = dripRate * 3;

    // if (currentVal > DRIPPING_THRESHOLD) {
    //     movingAvg = ADAPTIVE_TH_ALPHA * currentVal +
    //                 (1 - ADAPTIVE_TH_ALPHA) * oldMovingAvg;
    //     adaptiveThreshold = movingAvg - 0.03;
    //     oldMovingAvg = movingAvg;
    // }

    // debugMessage(INFO, "[ " + String(diffVal) + " ]" +
    //                       " Threshold: " + String(drippingThreshold) +
    //                       " Drip Count: " + String(dripCount) +
    //                       " Drip Rate: " + String(dripRate) +
    //                       " Flow Rate: " + String(flowRate));
    debugMessage(INFO, String(diffVal) + "," +
                       String(drippingThreshold) + "," +
                       String(dripCount) + "," +
                       String(dripRate));

    // setFlowRate(flowRate);
}

void monitorUrineOutput() {
    urineOut = 0.0;
    for (uint8_t i = 0; i < 5; i++){
        urineOut += scale.get_units();
    }
    urineOut = urineOut / 5;
    if (urineOut < 0) urineOut = 0;


    // weightSamples.add(scale.get_units());
    // urineOut = weightSamples.getAverage();
    // if (urineOut < 0) urineOut = 0;
    debugMessage(INFO, "Urine Output: " + String(urineOut));
}

void sendDispenserState() {
    publishData(
        flowRate,
        dripRate,
        urineOut,
        alertMessage);

    lcdClearVal();
    lcd.setCursor(3, 0);
    lcd.print(dripRate, 1);
    lcd.setCursor(11, 0);
    lcd.print(dripCount);
    lcd.setCursor(3, 1);
    lcd.print((uint16_t)urineOut);
    lcd.setCursor(11, 1);
    lcd.print(position);
}

void lcdTemplate()
{
    lcd.setCursor(3, 0);
    lcd.print("AUTOMATIC");
    lcd.setCursor(1, 1);
    lcd.print("I/V DISPENSER");
    delay(2000);
    lcd.clear();
    delay(200);

    lcd.setCursor(0, 0);
    lcd.print("DR:");
    lcd.setCursor(8, 0);
    lcd.print("DC:");
    lcd.setCursor(0, 1);
    lcd.print("UO:");
    lcd.setCursor(8, 1);
    lcd.print("MP:");
}

void lcdClearVal()
{
    lcd.setCursor(3, 0);
    lcd.print("     ");
    lcd.setCursor(11, 0);
    lcd.print("     ");
    lcd.setCursor(3, 1);
    lcd.print("     ");
    lcd.setCursor(11, 1);
    lcd.print("     ");
}