#include "utils.h"

void inialializeBluetooth() {
    debugMessage(LOADING, "Starting bluetooth ... ");
    Bluetooth.begin(BLUETOOTH_NAME);
    debugMessage(SUCCESS, "Bluetooth initialized ... ");
}