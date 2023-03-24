#include "Tick.h"

#include <cassert>


void controller::Tick::Start()
{
    assert(!isRunning);

    isPaused = false;
    isRunning = true;

    std::thread([&]()
    { 
        while (isRunning)
        { 
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            if(!isPaused) func();
            std::this_thread::sleep_until(x);
        }
    }).detach();

}
