#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Knightrider.h"

TEST_CASE("Knightrider", "[knightrider]") {
    struct : LedDriver {
        void setState(bool on) {
            this->on = on;
        }
        bool on = false;
    } led0, led1, led2, led3;

    Knightrider knightrider;
    knightrider.leds[0] = &led0;
    knightrider.leds[1] = &led1;
    knightrider.leds[2] = &led2;
    knightrider.leds[3] = &led3;
    knightrider.init();

    size_t steps = 0;

    SECTION("led 0 on") {
        SECTION("0 steps") { steps = 0; }
        SECTION("6 steps") { steps = 6; }
        SECTION("12 steps") { steps = 12; }
        SECTION("1 steps, paused") { knightrider.pause(); steps = 1; }
        SECTION("2 steps, paused") { knightrider.pause(); steps = 2; }
        SECTION("3 steps, paused") { knightrider.pause(); steps = 3; }
        SECTION("4 steps, paused") { knightrider.pause(); steps = 4; }
        SECTION("5 steps, paused") { knightrider.pause(); steps = 5; }
        SECTION("7 steps, paused") { knightrider.pause(); steps = 7; }

        for(size_t i = 0; i < steps; ++i) knightrider.step();

        CAPTURE(steps);
        REQUIRE(led0.on == true);
        REQUIRE(led1.on == false);
        REQUIRE(led2.on == false);
        REQUIRE(led3.on == false);
    }
    SECTION("led 1 on") {
        SECTION("1 step") { steps = 1; }
        SECTION("5 steps") { steps = 5; }
        SECTION("7 steps") { steps = 7; }
        SECTION("11 steps") { steps = 11; }
        SECTION("13 steps") { steps = 13; }

        for(size_t i = 0; i < steps; ++i) knightrider.step();

        CAPTURE(steps);
        REQUIRE(led0.on == false);
        REQUIRE(led1.on == true);
        REQUIRE(led2.on == false);
        REQUIRE(led3.on == false);
    }
    SECTION("led 2 on") {
        SECTION("2 steps") { steps = 2; }
        SECTION("4 steps") { steps = 4; }
        SECTION("8 steps") { steps = 8; }
        SECTION("10 steps") { steps = 10; }
        SECTION("14 steps") { steps = 14; }

        for(size_t i = 0; i < steps; ++i) knightrider.step();

        CAPTURE(steps);
        REQUIRE(led0.on == false);
        REQUIRE(led1.on == false);
        REQUIRE(led2.on == true);
        REQUIRE(led3.on == false);
    }
    SECTION("led 3 on") {
        SECTION("3 steps") { steps = 3; }
        SECTION("9 steps") { steps = 9; }
        SECTION("15 steps") { steps = 15; }

        for(size_t i = 0; i < steps; ++i) knightrider.step();

        CAPTURE(steps);
        REQUIRE(led0.on == false);
        REQUIRE(led1.on == false);
        REQUIRE(led2.on == false);
        REQUIRE(led3.on == true);
    }
}
