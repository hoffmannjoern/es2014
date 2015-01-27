#include "Knightrider.h"

#include <util/delay.h>

Knightrider::Knightrider(uint16_t delay) : delay(delay), currentLed(0), running(true), secondStage(false) {}

void Knightrider::step() {
    if(running) {
        size_t currentLed = getCurrentLedIndex();

        leds[currentLed]->turnOn();
        _delay_ms(delay);
        leds[currentLed]->turnOff();

        if(running) {
            proceedLedIndex();
        }
    }
}

void Knightrider::run() {
    while(true) {
        step();
    }
}

void Knightrider::pause() {
    running = false;
}
void Knightrider::resume() {
    running = true;
}

size_t Knightrider::getCurrentLedIndex() {
    return currentLed;
}
void Knightrider::proceedLedIndex() {
    size_t maxIndex = sizeof(leds) / sizeof(LedDriver*) - 1;

    if(currentLed == maxIndex) {
        secondStage = true;
    }
    if(currentLed == 0) {
        secondStage = false;
    }

    secondStage ? currentLed-- : currentLed++;
}
