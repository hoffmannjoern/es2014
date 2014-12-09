#Aufgabenblatt 1
##Aufgabe 4
###Lassen Sie die `SLIDER_LED2` abhängig vom analogen Wert des `SLIDER2` heller oder dunkler leuchten.
1. **Wie funktioniert die AD-Konvertierung beim AVR und Arduino?**

    > The Atmega controllers used for the Arduino contain an onboard 6 channel analog-to-digital (A/D) converter. The converter has 10 bit resolution, returning integers from 0 to 1023. While the main function of the analog pins for most Arduino users is to read analog sensors, the analog pins also have all the functionality of general purpose input/output (GPIO) pins (the same as digital pins 0 - 13).

    Quelle: [http://arduino.cc/en/Tutorial/AnalogInputPins](http://arduino.cc/en/Tutorial/AnalogInputPins)
2. **Wie funktioniert die DA-Konvertierung beim AVR und Arduino?**

    `analogWrite(pin, value)`
    > After a call to `analogWrite()`, the pin will generate a steady square wave of the specified duty cycle until the next call to `analogWrite()` (or a call to `digitalRead()` or `digitalWrite()` on the same pin). The frequency of the PWM signal on most pins is approximately 490 Hz. On the Uno and similar boards, pins 5 and 6 have a frequency of approximately 980 Hz. Pins 3 and 11 on the Leonardo also run at 980 Hz.

    Quelle: [http://arduino.cc/en/Tutorial/AnalogInputPins](http://arduino.cc/en/Tutorial/AnalogInputPins)

###Benutzt
* LED-Slider2   -> A1
* LED-Slide LED -> D10
