#include "Tick.h"

void environment::Tick::Start()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void environment::Tick::End()
{
    endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = endTime - startTime;
    float elapsed = duration.count();

    if (elapsed < deltaTime && !isPaused)
    {
        std::this_thread::sleep_for(std::chrono::duration<float>(deltaTime - elapsed));
        elapsed = deltaTime;
    }

    fps = 1.0f / elapsed;
}
