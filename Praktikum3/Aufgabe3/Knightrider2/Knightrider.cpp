#include "Knightrider.h"

Knightrider::Knightrider() : currentLed(0), running(true), secondStage(false) {}

void Knightrider::init() {
    leds[0]->turnOn();
    leds[1]->turnOff();
    leds[2]->turnOff();
    leds[3]->turnOff();
}

void Knightrider::step() {
    if(running) {
        leds[getCurrentLedIndex()]->turnOff();
        proceedLedIndex();
        leds[getCurrentLedIndex()]->turnOn();
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
