#ifndef LED_H
#define LED_H

#include "WProgram.h"

class LED
{ 
	public:
		LED();
		~LED();
		void writeSevenSeg(int number);
		int readSliderValue();
};

#endif