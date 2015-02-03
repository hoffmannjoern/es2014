#ifndef _PINGROUPDRIVER_H_
#define _PINGROUPDRIVER_H_

#include <avr/io.h>

class PinGroupDriver {
  public:
    PinGroupDriver();
    
    void setup();
       
    bool isPinLowActive(uint8_t pin_nr); 
    void setPinLowActive(uint8_t pin_nr);
    void enablePin(uint8_t pin_nr);
    void disablePin(uint8_t pin_nr);
    void disableAllPins();    
    
  private:
    void setPORT(uint8_t value);
    uint8_t getPORT();
    void setPORTLowActive(uint8_t ports);
    uint8_t getPORTLowActive();
    
    uint8_t check_0_8(uint8_t pin_nr);
    
    uint8_t LOW_ACTIVE_PORTS;
};

#endif _PINGROUPDRIVER_H_
