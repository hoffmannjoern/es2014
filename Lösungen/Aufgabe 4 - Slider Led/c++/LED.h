#ifndef LED_H
#define LED_H

#include "WProgram.h"

class LED
{ 
	public:
		LED();
		~LED();
		void changeLedValue( int sensorValue)
};

#endif