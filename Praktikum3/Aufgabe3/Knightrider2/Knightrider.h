#ifndef _KNIGHTRIDER_H_
#define _KNIGHTRIDER_H_

#include "LedDriver.h"

#include <stdint.h>
#include <stddef.h>

class Knightrider {
    public:
        Knightrider(uint16_t delay);

        void step();
        void run();

        void pause();
        void resume();

        LedDriver* leds[4];

    private:
        volatile bool running;
        uint16_t delay;

        size_t currentLed;
        bool secondStage;

        size_t getCurrentLedIndex();
        void proceedLedIndex();
};

#endif
