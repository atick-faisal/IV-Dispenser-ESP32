#ifndef LOGGER_
#define LOGGER_

#include <Arduino.h>
#include "../config/config.h"

enum DebugLevel {
    INFO,
    SUCCESS,
    LOADING,
    ERROR
};

// ... Logging utils
void initializeDebugLog();
void debugMessage(DebugLevel debugLevel, const String message);

#endif