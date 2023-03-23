#include "Tick.h"

#include "doctest.h"
#include "cmath"


TEST_SUITE("Tick")
{
    TEST_CASE("Basic functionality")
    {

        environment::Tick tick(60);
        float expectedDeltaTime = 1.0f / 60;

        // Check initial values
        CHECK(tick.GetFPS() == 60);
        CHECK(tick.GetDeltaTime() == doctest::Approx(expectedDeltaTime).epsilon(0.01));

        // Check tick time
        tick.Start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        tick.End();

        CHECK(tick.GetDeltaTime() == doctest::Approx(expectedDeltaTime).epsilon(0.01));
        CHECK(tick.GetFPS() == doctest::Approx(60).epsilon(20));
    };

    TEST_CASE("Pausing and resuming")
    {
        environment::Tick tick(60);
        float expectedDeltaTime = 1.0f / 60;

        // Check initial values
        CHECK(tick.GetFPS() == 60);
        CHECK(tick.GetDeltaTime() == doctest::Approx(expectedDeltaTime).epsilon(0.01));
        CHECK_FALSE(tick.IsPaused());

        // Pause the tick
        tick.Pause();
        CHECK(tick.IsPaused());

        // Check that tick time is not advancing when paused
        tick.Start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        tick.End();

        CHECK(tick.GetDeltaTime() == doctest::Approx(0).epsilon(0.01));
        CHECK(tick.GetFPS() == doctest::Approx(0).epsilon(0.01));

        // Resume the tick
        tick.Resume();
        CHECK_FALSE(tick.IsPaused());

        // Check that tick time is advancing again after resuming
        tick.Start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        tick.End();

        CHECK(tick.GetDeltaTime() == doctest::Approx(expectedDeltaTime).epsilon(0.01));
        CHECK(tick.GetFPS() == doctest::Approx(60).epsilon(0.01));
    }
}
