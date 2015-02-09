#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Timer.h"

TEST_CASE("Timer<1> with 16 MHz clock, 16k divider", "[timer]") {
    Timer<1> timer(16'000'000, 16'000);

    struct TimerCallback : public Timer<1>::Callback {
        void run() {
            ++count;
        }
        uint16_t getTime_ms() {
            return time;
        }
        unsigned long count = 0;
        uint16_t time = 0;
    } timerCallback;

    timer.addCallback(&timerCallback);

    SECTION("0ms callback") {
        timerCallback.time = 0;

        SECTION("0 ticks") {
            REQUIRE(timerCallback.count == 0);
        }
        SECTION("1000 tick") {
            for(size_t i = 0; i < 1000; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 0);
        }
        SECTION("1000000 tick") {
            for(size_t i = 0; i < 1000000; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 0);
        }
    }
    SECTION("1ms callback") {
        timerCallback.time = 1;

        SECTION("0 ticks") {
            REQUIRE(timerCallback.count == 0);
        }
        SECTION("1 tick") {
            for(size_t i = 0; i < 1; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 1);
        }
        SECTION("1000 ticks") {
            for(size_t i = 0; i < 1000; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 1000);
        }
    }
    SECTION("500ms callback") {
        timerCallback.time = 500;

        SECTION("1 tick") {
            for(size_t i = 0; i < 1; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 0);
        }
        SECTION("500 ticks") {
            timerCallback.time = 500;
            for(size_t i = 0; i < 500; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 1);
        }
        SECTION("1000 ticks") {
            timerCallback.time = 500;
            for(size_t i = 0; i < 1000; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 2);
        }
    }
    SECTION("800ms callback") {
        timerCallback.time = 800;

        SECTION("2500 ticks") {
            for(size_t i = 0; i < 2500; ++i) timer.__tick();

            REQUIRE(timerCallback.count == 3);
        }
    }
}
