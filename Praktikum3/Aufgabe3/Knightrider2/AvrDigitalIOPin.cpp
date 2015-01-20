#include "AvrDigitalIOPin.h"

#include <avr/io.h>

AvrDigitalIOPin::AvrDigitalIOPin(Port port, Pin pin, Direction direction) : DigitalIOPin(direction), pin(pin) {
    initPort(port);
    setDirection(direction);
}

void AvrDigitalIOPin::setDirection(Direction direction) {
    DigitalIOPin::setDirection(direction);

    if(direction == Input) {
        *ddr &= ~(1<<pin);
    } else {
        *ddr |= 1<<pin;
    }
}

void AvrDigitalIOPin::writeValue(bool value) {
    if(direction == Input) {
        //throw std::logic_error("Can not write in input mode.");
    }

    if(value) {
        *out |= 1<<pin;
    } else {
        *out &= ~(1<<pin);
    } 
}

bool AvrDigitalIOPin::readValue() {
    if(direction == Output) {
        //throw std::logic_error("Can not read in output mode.");
    }

    return *in & 1<<pin;
}

void AvrDigitalIOPin::initPort(Port port){
    switch(port) {
        case PortB:
            ddr = &DDRB;
            out = &PORTB;
            in = &PINB;
            break;
        case PortC:
            ddr = &DDRC;
            out = &PORTC;
            in = &PINC;
            break;
        case PortD:
            ddr = &DDRD;
            out = &PORTD;
            in = &PIND;
            break;
    }
}

