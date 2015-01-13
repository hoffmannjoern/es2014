#ifndef _LOWACTIVELEDDRIVER_H_
#define _LOWACTIVELEDDRIVER_H_

#include "LedDriverImpl.h"

class LowActiveLedDriver : public LedDriverImpl {
    public:
        LowActiveLedDriver(DigitalIOPin& pin) : LedDriverImpl(pin) {}
    protected:
        virtual void setState(bool on);
};

#endif

