#include "utils.h"

String getDeviceId() {
    return "IVD_" + WiFi.macAddress();
}