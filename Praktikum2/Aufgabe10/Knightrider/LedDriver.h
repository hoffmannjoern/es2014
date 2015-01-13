#ifndef _LEDDRIVER_H_
#define _LEDDRIVER_H_

class LedDriver {
    public:
        void turnOn() {
            setState(true);
        }
        void turnOff() {
            setState(false);
        }
    protected:
        virtual void setState(bool on) = 0;
};

#endif
