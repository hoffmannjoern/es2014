#include "HighActiveLedDriver.h"

void HighActiveLedDriver::setState(bool on) {
    pin.writeValue(on);
}
