#include <avr/io.h>
#include <util/delay.h>

uint8_t LOW_ACTIVE_PORTS = B00000000;

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
  Serial.print("PORTD = ");
  Serial.print(PORTD, BIN);
  PORTD = value ^ getPORTLowActive();
  Serial.print(" -> ");
  Serial.println(PORTD, BIN);
}

void u8g_Delay(uint16_t val)
{
  // https://www.google.de/url?sa=t&rct=j&q=&esrc=s&source=web&cd=6&ved=0CE8QFjAF&url=https%3A%2F%2Fdownload.lulzbot.com%2FTAZ%2F2.0%2Fsoftware%2F2013Q4%2Ffirmware%2Farduino-1.0.5%2Flibraries%2FU8glib%2Futility%2Fu8g_delay.c&ei=-D-1VJ7YKcHcasb3gLgE&usg=AFQjCNEtlZFCXsMOiUIZLdrYz42iMwCTRw&bvm=bv.83339334,d.d2s&cad=rja
  /* old version did a call to the arduino lib: delay(val); */
  while( val != 0 )
  {
    _delay_loop_2( (F_CPU / 4000 ) -2);
    val--;
  }
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
    Serial.print("LED = ");
    Serial.print(led_nr);
    Serial.println(" is low active!");
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

void inline blinkLED(uint8_t led_nr, uint16_t delay_in_ms) {
  Serial.print("Blink LED = ");
  Serial.print(led_nr);
  Serial.print(" for ");
  Serial.print(delay_in_ms);
  Serial.println(" ms.");
  // enable LED
  enableLED(led_nr);
  // delay
  u8g_Delay(delay_in_ms);
  // disable LED
  disableLED(led_nr);
}

void inline knight_rider() {
  blinkLED(6, 600);
  blinkLED(5, 400);
  blinkLED(4, 400);
  blinkLED(3, 600);
  blinkLED(4, 400);
  blinkLED(5, 400);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start program ...");
  setupLEDPorts();
}

void loop() {
  knight_rider();  
}