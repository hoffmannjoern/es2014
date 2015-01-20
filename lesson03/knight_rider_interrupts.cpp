#include <avr/io.h>
#include <avr/interrupt.h>

// Used LED pins
#define LED_1 6
#define LED_2 5
#define LED_3 4
#define LED_4 3
// Taster pin
#define TASTER_PIN 2

enum KNIGHT_RIDER_LED_POS {
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED5 = 4,
  LED6 = 5
};

// states
uint8_t LOW_ACTIVE_PORTS = B00000000;
volatile boolean KNIGHT_RIDER_ENABLED = false; // to disable knight rider

volatile KNIGHT_RIDER_LED_POS LED_POS; // Position of LED Light 

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
  digitalWrite(TASTER_PIN, HIGH);
  
  // Enable interrupts
  sei();
  EIMSK |= (1 << INT0); // Enable interrupt on INT0 (Pin 2)
  EICRA |= (1 << ISC01); // Trigger interrupt on falling edge
}

void inline setupLEDPorts() {
  // Set output ports
  DDRD = B11111110;
  // Bits 5 & 4 are low active
  setPORTLowActive(B00110000);
  // Set initial output values
  setPORT(B00110000);
}

void inline setPORTLowActive(uint8_t ports) {
  LOW_ACTIVE_PORTS = ports;
}

uint8_t inline getPORTLowActive() {
  return LOW_ACTIVE_PORTS;
}

uint8_t inline getPORT() {
  return PORTD ^ getPORTLowActive();
}

void inline setPORT(uint8_t value) {
  // Serial.print("PORTD = ");
  // Serial.print(PORTD, BIN);
  PORTD = value ^ getPORTLowActive();
  // Serial.print(" -> ");
  // Serial.println(PORTD, BIN);
}

uint8_t inline checkLEDNr(uint8_t led_nr) {
  // check: not lower
  if (led_nr < 0) led_nr = 0;
  // check: not higher
  if (led_nr > 7) led_nr = 7;
  // return value or defaults
  return led_nr;
}

boolean inline isLowActive(uint8_t led_nr) {
  return B00000000 != (getPORTLowActive() & (1 << checkLEDNr(led_nr)));
}

void inline enableLED(uint8_t led_nr) {
  if (isLowActive(led_nr)) {
    // Serial.print("LED = ");
    // Serial.print(led_nr);
    // Serial.println(" is low active!");
  }
  
  led_nr = checkLEDNr(led_nr);
  // enable given LED pin
  setPORT(getPORT() | (1 << led_nr));
}

void inline disableLED(uint8_t led_nr) {
  led_nr = checkLEDNr(led_nr);
  // enable all LED pins other than the given one
  setPORT(getPORT() & (~(1 << led_nr)));
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start program ...");
  setupLEDPorts();
  setupInterrupts();
  setupTimerInterrupts();
}

void loop() {  
  KNIGHT_RIDER_LED_POS led_to_disable = LED_POS;
  KNIGHT_RIDER_LED_POS led_to_enable = (KNIGHT_RIDER_LED_POS) ((LED_POS + 1) % 6);
  
  switch(led_to_disable) {
    case LED1:
      disableLED(LED_1);
      break;
    case LED2:
    case LED6:
      disableLED(LED_2);
      break;
    case LED3:
    case LED5:
      disableLED(LED_3);
      break;
    case LED4:
      disableLED(LED_4);
      break;
  }
  
  switch(led_to_enable) {
    case LED1:
      enableLED(LED_1);
      break;
    case LED2:
    case LED6:
      enableLED(LED_2);
      break;
    case LED3:
    case LED5:
      enableLED(LED_3);
      break;
    case LED4:
      enableLED(LED_4);
      break;
  }
}

ISR(INT0_vect)
{
  KNIGHT_RIDER_ENABLED = !KNIGHT_RIDER_ENABLED;
}

ISR(TIMER1_COMPA_vect)
{
  LED_POS = (KNIGHT_RIDER_LED_POS)((LED_POS + 1) % 6);
  
  Serial.print("LED to blink: ");Serial.println(LED_POS);
}