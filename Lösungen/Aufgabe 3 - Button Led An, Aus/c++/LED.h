#ifndef LED_H
#define LED_H

#include "WProgram.h"

class LED
{ 
	public:
		LED();
		~LED();
		void on();
		void off();
		int readButtonState(int pin);
};

#endif