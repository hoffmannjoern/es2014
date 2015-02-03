#include "KnightRider.h"

// Constructor
KnightRider::KnightRider(PinGroupDriver &pins) : leds(pins) {}

void KnightRider::setup() {
  // empty ...
}

void KnightRider::start() {
  _isRunning = true;
}

void KnightRider::stop() {
  _isRunning = false;
}

void KnightRider::nextLED() {
  // only change state if running
  if (_isRunning) {
    // switch to next led state
    LED_POS = (KNIGHT_RIDER_LED_POS)((LED_POS + 1) % 6);
    _changedState = true;
  }
}

void KnightRider::show() {
  // stop to many changes ...
  if (!_changedState) {
    return;
  } else {
    _changedState = false;
  }
  
  // compute leds to change
  KNIGHT_RIDER_LED_POS led_to_disable = LED_POS;
  KNIGHT_RIDER_LED_POS led_to_enable = (KNIGHT_RIDER_LED_POS) ((LED_POS + 1) % 6);
  
  // leds to disable
  switch(led_to_disable) {
    case LED1:
      leds.disablePin(LED_1);
      break;
    case LED2:
    case LED6:
      leds.disablePin(LED_2);
      break;
    case LED3:
    case LED5:
      leds.disablePin(LED_3);
      break;
    case LED4:
      leds.disablePin(LED_4);
      break;
  }
  
  // leds to enable
  switch(led_to_enable) {
    case LED1:
      leds.enablePin(LED_1);
      break;
    case LED2:
    case LED6:
      leds.enablePin(LED_2);
      break;
    case LED3:
    case LED5:
      leds.enablePin(LED_3);
      break;
    case LED4:
      leds.enablePin(LED_4);
      break;
  }
}

bool KnightRider::isRunning() {
  return _isRunning;
}


