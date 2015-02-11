#include "AvrDigitalIOPin.h"
#include "LedDriver.h"
#include "HighActiveLedDriver.h"
#include "LowActiveLedDriver.h"
#include "Knightrider.h"
#include "Timer.h"

#include <avr/interrupt.h>

Knightrider knightrider;
class KnightriderCallback : public Timer<1>::Callback {
    void run() {
        knightrider.step();
    }
    uint16_t getTime_ms() {
        return 500;
    }
} knightriderCallback;

AvrDigitalIOPin pin0(PortD, Pin0, Input);
AvrDigitalIOPin pin1(PortD, Pin1, Input);

AvrDigitalIOPin pin2(PortD, Pin2, Output);
AvrDigitalIOPin pin3(PortD, Pin3, Output);
AvrDigitalIOPin pin4(PortD, Pin4, Output);
AvrDigitalIOPin pin5(PortD, Pin5, Output);
LowActiveLedDriver led1(pin2);
LowActiveLedDriver led2(pin3);
HighActiveLedDriver led3(pin4);
HighActiveLedDriver led4(pin5);

Timer<1> timer(16000000, 16000);

void setup() {
    //Serial.begin(9600);

    timer.addCallback(&knightriderCallback);

    knightrider.leds[0] = &led1;
    knightrider.leds[1] = &led2;
    knightrider.leds[2] = &led3;
    knightrider.leds[3] = &led4;
    knightrider.init();

    // setup port D pin 0 and 1 interrupt
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT16);
    PCMSK2 |= (1 << PCINT17);

    // setup timer with 256 divider
    TCCR2B &= 0b00001000;
    TCCR2B |= (1 << CS10) | (1 << CS11) | (0 << CS12); // prescaler 64
    OCR2A = 500 - 1;
    TIMSK2 |= 1 << OCIE2A;

    // enable interrupts
    sei();
}

void loop() {
    //knightrider.run();
}

ISR(PCINT2_vect) {
    if(pin1.readValue()) {
        knightrider.pause();
    } else if(!pin0.readValue()) {
        knightrider.resume();
    }
}

ISR(TIMER2_COMPA_vect) {
    timer.__tick();
}
