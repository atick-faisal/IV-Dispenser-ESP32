#include "monitor.h"

#define SENSE_PIN 34
#define THRESHOLD 3000
#define N_DRIP 5

uint16_t current_val = 0;
unsigned long t_init = millis();
bool drip_flag = false;
uint8_t drip_count = 0;
uint16_t duration_buffer = 0;
float drip_rate = 0;
float flow_rate = 0;

// float flowRate = (float)random(0, 100);
// float drip_rate = (float)random(20, 120);
float urineOut = (float)random(0, 1000);

String alertMessage = "";

// void setup() {
//   Serial.begin(9600);

//   t_init = millis();
// }

// void loop() {
//   current_val = analogRead(SENSE_PIN);

//   if((current_val < THRESHOLD) && (drip_flag == false)) {
//     duration_buffer += millis() - t_init;
//     drip_flag = true;
//     t_init = millis();
//     drip_count++;
//   }
//   else if ((current_val > THRESHOLD) && (drip_flag == true) && ((millis() - t_init) > 100)) {
//     drip_flag = false;
//     if (drip_count == N_DRIP) {
//       drip_count = 0;
//       drip_rate = N_DRIP * 60000 / (float)duration_buffer;
//       duration_buffer = 0;

//     }
//   }

//   Serial.print(current_val);
//   Serial.print(",");
//   Serial.print(drip_count);
//   Serial.print(",");
//   Serial.print(drip_rate);
//   Serial.print("\n");
// }

void monitorDispenserState() {
    current_val = analogRead(SENSE_PIN);

    if ((current_val < THRESHOLD) && (drip_flag == false)) {
        duration_buffer += millis() - t_init;
        drip_flag = true;
        t_init = millis();
        drip_count++;
    } else if ((current_val > THRESHOLD) && (drip_flag == true) && ((millis() - t_init) > 100)) {
        drip_flag = false;
        if (drip_count == N_DRIP) {
            drip_count = 0;
            drip_rate = N_DRIP * 60000 / (float)duration_buffer;
            flow_rate = drip_rate * 3;
            duration_buffer = 0;
        }
    }

    debugMessage(INFO, "Drip Rate: " + String(drip_rate) +
                           " Flow Rate: " + String(flow_rate));

    setFlowRate(flow_rate);
}

void sendDispenserState() {
    publishData(flow_rate, drip_rate, urineOut, alertMessage);
}