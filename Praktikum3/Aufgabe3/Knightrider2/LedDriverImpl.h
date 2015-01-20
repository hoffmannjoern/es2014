#ifndef _LEDDRIVERIMPL_H_
#define _LEDDRIVERIMPL_H_

#include "DigitalIOPin.h"
#include "LedDriver.h"

class LedDriverImpl : public LedDriver {
    public:
        LedDriverImpl(DigitalIOPin& pin) : pin(pin) {}
    protected:
        virtual void setState(bool on) = 0;
        DigitalIOPin& pin;
};

#endif
