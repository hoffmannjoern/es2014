#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "PinGroupDriver.h"
#include "KnightRider.h"

// Taster pin
#define TASTER_PIN 2
#define TASTER_PIN2 3

// Classes

PinGroupDriver leds;
KnightRider knightRider(leds);

// Setup functions

void inline setupTimerInterrupts() {
  cli();
  
  // clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  TIMSK1 = (1 << TOIE1); // Use TIMER1
  TCCR1B |= (1 << WGM12);
  TCCR1B |= ((1 << CS10) | (1 << CS12)); // Use timer with 1024 prescalar
  
  // s. Artikel
  OCR1A = 15624; //(1 / (F_CPU / 1024)) - 1; // timer compare match register
  TIMSK1 = (1 << OCIE1A); // Enable timer compare interrupt
  
  sei();
}

void setupWatchdog() {
  // Set watchdog timer to 4 seconds
  wdt_enable(WDTO_4S);
}  
  
void inline setupInterrupts() {
  // Set taster input pin with initial value
  pinMode(TASTER_PIN, INPUT);
  pinMode(TASTER_PIN2, INPUT);
  digitalWrite(TASTER_PIN, HIGH);
  digitalWrite(TASTER_PIN2, HIGH);
  
  // Enable interrupts
  sei();
  EIMSK |= (1 << INT0); // Enable interrupt on INT0 (Pin 2)
  EIMSK |= (1 << INT1);
  EICRA |= (1 << ISC01); // Trigger interrupt on falling edge
  EICRA |= (1 << ISC11); // Trigger interrupt on falling edge
  
  // Call watchdog somehow
  // EICRA |= (1 << ISC00);
}

// Arduino main functions

void setup() {
  Serial.begin(9600);
  Serial.println("Start program ...");
  
  leds.setup();
  leds.setPinLowActive(LED_2);
  leds.setPinLowActive(LED_3);
  knightRider.setup();
  
  setupInterrupts();
  setupTimerInterrupts();
  setupWatchdog();
}

void loop() {
  // Reset watchdog timer
  wdt_reset();
  
  if (knightRider.isRunning()) {
    knightRider.show();
  }
}

// Interrupt handler

ISR(INT0_vect) {
  Serial.println("Weiter ...");
  knightRider.start();
}

ISR(INT1_vect) {
  Serial.println("Stop ...");
  knightRider.stop();
}

ISR(TIMER1_COMPA_vect) {
  if (knightRider.isRunning()) {
    knightRider.nextLED();
  }  
}
