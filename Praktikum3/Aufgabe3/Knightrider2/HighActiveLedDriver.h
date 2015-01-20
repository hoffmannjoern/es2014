#ifndef _HIGHACTIVELEDDRIVER_H_
#define _HIGHACTIVELEDDRIVER_H_

#include "LedDriverImpl.h"

class HighActiveLedDriver : public LedDriverImpl {
    public:
        HighActiveLedDriver(DigitalIOPin& pin) : LedDriverImpl(pin) {}
    protected:
        virtual void setState(bool on);
};

#endif

