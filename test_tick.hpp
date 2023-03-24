#include <chrono>
#include <thread>
#include <iostream>
#include <stdexcept>

#include "doctest.h"

#include "Tick.h"

using namespace controller;

TEST_SUITE("Test Tick")
{
    TEST_CASE("Tick Start() method")
    {
        SUBCASE("Start a Tick and then Stop it")
        {
            bool tickCalled = false;
            int fps = 10;
            Tick t([&]()
                   { tickCalled = true; },
                   fps);
            t.Start();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            t.Stop();
            CHECK(tickCalled);
        }

        SUBCASE("Tick should call the function at the specified FPS")
        {
            int fps = 30;
            Tick t([&]()
                   { std::this_thread::sleep_for(std::chrono::milliseconds(20)); },
                   fps);
            t.Start();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            t.Stop();
            auto actualFPS = 1000.0f / t.GetInterval();
            CHECK(actualFPS == doctest::Approx(fps).epsilon(0.1));
        }

        SUBCASE("Pause and resume a running Tick")
        {
            bool tickCalled = false;
            Tick t([&]()
                   { tickCalled = true; },
                   30);
            t.Start();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            t.Pause();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            t.Resume();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            t.Stop();
            CHECK(tickCalled);
        }
    }
}
