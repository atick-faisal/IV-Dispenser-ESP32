#include "utils.h"

void initializeDebugLog() {
#ifdef DEBUG
    Serial.begin(115200);
    while (!Serial) {
        ;  // ... Wait for serial port to connect
    }
#endif
}

void debugMessage(DebugLevel debugLevel, const String message) {
#ifdef DEBUG
    String debugMessage;
    switch (debugLevel) {
        case INFO:
            debugMessage = "[ i ] " + message;
            break;

        case SUCCESS:
            debugMessage = "[ ✓ ] " + message;
            break;

        case LOADING:
            debugMessage = "[ ● ] " + message;
            break;

        case ERROR:
            debugMessage = "[ ✕ ] " + message;
            break;

        default:
            debugMessage = "[ i ] " + message;
            break;
    }
    Serial.println(debugMessage);
#endif
}