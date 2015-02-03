#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "PinGroupDriver.h"

// Used LED pins
#define LED_1 7
#define LED_2 6
#define LED_3 5
#define LED_4 4

// Taster pin
#define TASTER_PIN 2
#define TASTER_PIN2 3

enum KNIGHT_RIDER_LED_POS {
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED5 = 4,
  LED6 = 5
};

// states
volatile boolean KNIGHT_RIDER_ENABLED = false; // to disable knight rider
volatile KNIGHT_RIDER_LED_POS LED_POS; // Position of LED Light 

PinGroupDriver leds;

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
  
  // Call watchdog somehow
  // EICRA |= (1 << ISC00);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start program ...");
  
  leds.setup();
  leds.setPinLowActive(LED_2);
  leds.setPinLowActive(LED_3);
  
  setupInterrupts();
  setupTimerInterrupts();
  setupWatchdog();
}

boolean changed = false;
void loop() {
  // Reset watchdog timer
  wdt_reset();
  
  if (!KNIGHT_RIDER_ENABLED) {
    return;
  }
  
  // stop to many changes ...
  if (!changed) {
    return;
  } else {
    changed = false;
  }
  
  KNIGHT_RIDER_LED_POS led_to_disable = LED_POS;
  KNIGHT_RIDER_LED_POS led_to_enable = (KNIGHT_RIDER_LED_POS) ((LED_POS + 1) % 6);
 
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

ISR(INT0_vect) {
  Serial.println("Weiter ...");
  KNIGHT_RIDER_ENABLED = true;
}

ISR(INT1_vect) {
  Serial.println("Stop ...");
  KNIGHT_RIDER_ENABLED = false;
}

ISR(TIMER1_COMPA_vect) {
  if (! KNIGHT_RIDER_ENABLED) {
    return;
  }
  
  LED_POS = (KNIGHT_RIDER_LED_POS)((LED_POS + 1) % 6);
  changed = true;  
  Serial.print("LED to blink: ");Serial.println(LED_POS);
}
