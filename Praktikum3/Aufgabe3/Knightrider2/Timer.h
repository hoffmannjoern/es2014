#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <stddef.h>

template <size_t MaxCallbacks>
class Timer {
    public:
        Timer(uint32_t clock, uint32_t divider) : counter_tick(0) {
            ticksPerMillisecond = static_cast<uint16_t>(clock / 1000 / divider);
        }
        
        struct Callback {
            virtual void run();
            virtual uint16_t getTime_ms();
        };

        bool addCallback(Callback* callback) {
            for(size_t i = 0; i < MaxCallbacks; ++i) {
                if(!callbacks[i].callback) {
                    callbacks[i].callback = callback;
                    return true;
                }
            }
            return false;
        }
        bool removeCallback(Callback* callback) {
            for(size_t i = 0; i < MaxCallbacks; ++i) {
                if(callbacks[i].callback == callback) {
                    callbacks[i].callback = NULL;
                    return true;
                }
            }
            return false;
        }

        void __tick() {
            ++counter_tick;

            if(counter_tick == ticksPerMillisecond) {
                incrementTime();
                counter_tick = 0;
            }
        }

    private:
        uint16_t ticksPerMillisecond;
        uint16_t counter_tick;

        struct CallbackItem {
            CallbackItem() : callback(NULL), counter(0) {}
            Callback* callback;
            uint16_t counter;
        };

        CallbackItem callbacks[MaxCallbacks];

        void incrementTime() {
            for(size_t i = 0; i < MaxCallbacks; ++i) {
                if(callbacks[i].callback) {
                    ++callbacks[i].counter;
                    if(callbacks[i].counter == callbacks[i].callback->getTime_ms()) {
                        callbacks[i].callback->run();
                        callbacks[i].counter = 0;
                    }
                }
            }
        }
};

#endif
