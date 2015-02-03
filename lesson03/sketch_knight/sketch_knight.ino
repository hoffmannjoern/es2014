#include <avr/io.h>
#include <avr/interrupt.h>
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

void inline setupInterrupts() {
  // Set taster input pin with initial value
  pinMode(TASTER_PIN, INPUT);
  pinMode(TASTER_PIN2, INPUT);
  digitalWrite(TASTER_PIN, HIGH);
  digitalWrite(TASTER_PIN2, HIGH);
  
  // Enable interrupts
  sei();
  EIMSK |= (1 << INT0); // Enable interrupt on INT0 (Pin 2)
  EICRA |= (1 << ISC01); // Trigger interrupt on falling edge
  EIMSK |= (1 << INT1);
  EICRA |= (1 << ISC11);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start program ...");
  
  leds.setup();
  // Bits 6 & 5 are low active
  leds.setPinLowActive(0b00000000);//(1 << LED_2) | (1 << LED_3));
  
  setupInterrupts();
  setupTimerInterrupts();
}

boolean changed = false;
void loop() {
  if (!KNIGHT_RIDER_ENABLED) {
    return;
  }
  
  if (!changed) {
    return;
  } else {
    changed = false;
  }
  
  Serial.print("PORT: ");Serial.println(leds.getPORT(), BIN);
  
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
  LED_POS = (KNIGHT_RIDER_LED_POS)((LED_POS + 1) % 6);
  changed = true;
  
  Serial.print("LED to blink: ");Serial.println(LED_POS);
  
  KNIGHT_RIDER_LED_POS led_to_disable = LED_POS;
  KNIGHT_RIDER_LED_POS led_to_enable = (KNIGHT_RIDER_LED_POS) ((LED_POS + 1) % 6);
  Serial.print("LED on: ");
  switch(led_to_enable) {
    case LED1:
      Serial.println((uint8_t) LED_1);
      break;
    case LED2:
    case LED6:
      Serial.println((uint8_t) LED_2);
      break;
    case LED3:
    case LED5:
      Serial.println((uint8_t) LED_3);
      break;
    case LED4:
      Serial.println((uint8_t) LED_4);
      break;
  }
}
