#ifndef _DIGITALIOPIN_H_
#define _DIGITALIOPIN_H_

enum Direction {
    Input,
    Output
};

class DigitalIOPin {
    public:
        DigitalIOPin(Direction direction) : direction(direction) {}
        virtual ~DigitalIOPin() {}

        virtual void setDirection(Direction direction) {
            this->direction = direction;
        }
        virtual void writeValue(bool value) = 0;
        virtual bool readValue() = 0;
    protected:
        Direction direction;
};

#endif
