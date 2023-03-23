#ifndef TICK_H_
#define TICK_H_

#include <chrono>
#include <thread>

namespace environment
{

    class Tick
    {
    public:
        Tick(int fps) : fps(fps), deltaTime(1.0f / fps) {}

        void Start();
        void End();

        inline void Pause() {
            isPaused = true;
        }
        inline void Resume() {
            isPaused = false;
        }
        inline bool IsPaused() {
            return isPaused;
        }
        inline float GetDeltaTime() const
        {
            return isPaused ? 0 : deltaTime;
        }
        inline float GetFPS() const
        {
            return isPaused ? 0 : fps;
        }

    private:
        float fps;
        float deltaTime;
        bool isPaused = false;

        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
    };
}

#endif
