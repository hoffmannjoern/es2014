#include "AvrDigitalIOPin.h"
#include "LedDriver.h"
#include "HighActiveLedDriver.h"
#include "LowActiveLedDriver.h"
#include "Knightrider.h"

#include <avr/interrupt.h>

Knightrider knightrider(200);

AvrDigitalIOPin pin0(PortD, Pin0, Input);
AvrDigitalIOPin pin1(PortD, Pin1, Input);

void setup() {
    //Serial.begin(9600);
    size_t p;
}

void loop() {
    AvrDigitalIOPin pin2(PortD, Pin2, Output);
    AvrDigitalIOPin pin3(PortD, Pin3, Output);
    AvrDigitalIOPin pin4(PortD, Pin4, Output);
    AvrDigitalIOPin pin5(PortD, Pin5, Output);
    LowActiveLedDriver led1(pin2);
    LowActiveLedDriver led2(pin3);
    HighActiveLedDriver led3(pin4);
    HighActiveLedDriver led4(pin5);
    led1.turnOff();
    led2.turnOff();
    led3.turnOff();
    led4.turnOff();

    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT16);
    PCMSK2 |= (1 << PCINT17);
    sei();

    knightrider.leds[0] = &led1;
    knightrider.leds[1] = &led2;
    knightrider.leds[2] = &led3;
    knightrider.leds[3] = &led4;

    knightrider.run();
}

ISR(PCINT2_vect) {
    if(pin1.readValue()) {
        knightrider.pause();
    } else if(!pin0.readValue()) {
        knightrider.resume();
    }
}
