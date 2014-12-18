//Enumeration of the Danger Shields LED
enum LED : int
{
    LED1 = 6
};

//Klasse
class LEDDriver
{
    public:
    LEDDriver(LED_t led) : pinOut(Led)
    {
        setup();
    }
    
    inline void enable(bool enable = true) const
    {
        digitalWrite(pinOut, enable ? HIGH : LOW);
    }
    
    inline void disable() const
    {
        enable(false);
    }
    
    private:
    inline void setup()
    {
        pinMode(pinOut, OUTPUT);
    }
    
    const int pinOut;
};

//Hauptprogramm----------------------------------------

//Setup
void setup() 
{                
    LEDDriver led(LED1);
    led.enable();		  
}
void loop(){}


//Änderungen:
//Alles trennen (nur eine Verantwortung pro Funktion --> nur ein Grund für die Änderung)
// Typen einschränken damit keine fehlerhalften werte übergeben werden

