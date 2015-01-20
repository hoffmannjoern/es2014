#include "AvrDigitalIOPin.h"
#include "LedDriver.h"
#include "HighActiveLedDriver.h"
#include "LowActiveLedDriver.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile bool test = true;

class Knightrider {
    public:
        Knightrider(uint16_t delay) : delay(delay) {}

        void run() {
            for(;;) {
                if(test) {
                    for(size_t i = 0; i < 4; ++i) {
                        leds[i]->turnOn();
                        _delay_ms(delay);
                        leds[i]->turnOff();
                    }
                    for(size_t i = 2; i > 0; --i) {
                        leds[i]->turnOn();
                        _delay_ms(delay);
                        leds[i]->turnOff();
                    }
                }
            }
        }
        LedDriver* leds[4];
    private:
        uint16_t delay;
};

void setup() {}

void loop() {
    AvrDigitalIOPin pin2(PortD, Pin2, Output);
    AvrDigitalIOPin pin3(PortD, Pin3, Output);
    AvrDigitalIOPin pin4(PortD, Pin4, Output);
    AvrDigitalIOPin pin5(PortD, Pin5, Output);
    LowActiveLedDriver led1(pin2);
    LowActiveLedDriver led2(pin3);
    HighActiveLedDriver led3(pin4);
    HighActiveLedDriver led4(pin5);
    
    AvrDigitalIOPin pin6(PortD, Pin6, Input);
    AvrDigitalIOPin pin7(PortD, Pin7, Input);

    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT16);
    PCMSK2 |= (1 << PCINT17);
    sei();

    Knightrider knightrider(500);
    knightrider.leds[0] = &led1;
    knightrider.leds[1] = &led2;
    knightrider.leds[2] = &led3;
    knightrider.leds[3] = &led4;

    knightrider.run();
}

ISR(PCINT2_vect) {
   test = false;
}
