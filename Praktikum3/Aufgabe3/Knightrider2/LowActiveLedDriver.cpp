#include "LowActiveLedDriver.h"

void LowActiveLedDriver::setState(bool on) {
    pin.writeValue(!on);
}
