#ifndef _KNIGHTRIDER_H_
#define _KNIGHTRIDER_H_

#include "PinGroupDriver.h";

// Used LED pins
#define LED_1 7
#define LED_2 6
#define LED_3 5
#define LED_4 4

// States of knight rider leds
enum KNIGHT_RIDER_LED_POS {
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED5 = 4,
  LED6 = 5
};

class KnightRider {
  public:
    KnightRider(PinGroupDriver &pins);
    
    void setup();
    
    void start();
    void stop();
    bool isRunning();
    
    void nextLED();
    void show();
    
  private:
    PinGroupDriver &leds;
    bool _isRunning;
    bool _changedState;
    KNIGHT_RIDER_LED_POS LED_POS; // Position of LED Light (volatile?)
};

#endif _KNIGHTRIDER_H_
