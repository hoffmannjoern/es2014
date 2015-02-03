#include "PinGroupDriver.h"

// Constructor
PinGroupDriver::PinGroupDriver() : LOW_ACTIVE_PORTS(0b00000000) {}

void PinGroupDriver::setup() {
  // Set output ports
  DDRD = 0b11111110;
  // Set initial output values
  setPORT(0b00000000);
}

void PinGroupDriver::setPORTLowActive(uint8_t ports) {
  LOW_ACTIVE_PORTS = ports;
}

uint8_t PinGroupDriver::getPORTLowActive() {
  return LOW_ACTIVE_PORTS;
}

uint8_t PinGroupDriver::getPORT() {
  return PORTD ^ getPORTLowActive();
}

void PinGroupDriver::setPORT(uint8_t value) {
  PORTD = value ^ getPORTLowActive();
}

uint8_t PinGroupDriver::check_0_8(uint8_t pin_nr) {
  // check: not lower
  if (pin_nr < 0) pin_nr = 0;
  // check: not higher
  if (pin_nr > 7) pin_nr = 7;
  // return value or defaults
  return pin_nr;
}

bool PinGroupDriver::isPinLowActive(uint8_t led_nr) {
  return 0b00000000 != (getPORTLowActive() & (1 << check_0_8(led_nr)));
}

void PinGroupDriver::setPinLowActive(uint8_t pin_nr) {
  pin_nr = check_0_8(pin_nr);
  
  setPORTLowActive(getPORTLowActive() | (1 << pin_nr));
  setPORT(0b00000000); // clear all pins
}

void PinGroupDriver::enablePin(uint8_t pin_nr) {  
  pin_nr = check_0_8(pin_nr);
  // enable given pin
  setPORT(getPORT() | (1 << pin_nr));
}

void PinGroupDriver::disablePin(uint8_t pin_nr) {
  pin_nr = check_0_8(pin_nr);
  // enable all pins other than the given one
  setPORT(getPORT() & (~(1 << pin_nr)));
}

