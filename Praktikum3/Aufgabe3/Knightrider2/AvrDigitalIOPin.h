#ifndef _AVRDIGITALIOPIN_H_
#define _AVRDIGITALIOPIN_H_

#include "DigitalIOPin.h"

#include <stdint.h>

enum Port {
    PortB,
    PortC,
    PortD
};

enum Pin {
    Pin0 = 0,
    Pin1 = 1,
    Pin2 = 2,
    Pin3 = 3,
    Pin4 = 4,
    Pin5 = 5,
    Pin6 = 6,
    Pin7 = 7
};

class AvrDigitalIOPin : public DigitalIOPin {
    public:
        AvrDigitalIOPin(Port port, Pin pin, Direction direction);

        virtual void setDirection(Direction direction);
        virtual void writeValue(bool value);
        virtual bool readValue();

    private:
        void initPort(Port port);

        volatile uint8_t* ddr;
        volatile uint8_t* out;
        volatile uint8_t* in;
        Pin pin;
};

#endif
