#ifndef TICK_H_
#define TICK_H_

#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

namespace controller
{

    class Tick
    {
    public:
        explicit Tick(std::function<void()> func, int fps)
            : fps(fps), interval(1.0f / fps * 1000), func(func) {}
        virtual ~Tick() { this->Stop(); }

        void Start();
        inline void Stop() { isRunning = false; isPaused = false; }

        inline void Pause() {
            isPaused = true;
        }
        inline void Resume() {
            isPaused = false;
        }
        inline bool IsPaused() {
            return isPaused;
        }
        inline float GetInterval() const
        {
            return isPaused ? 0 : interval;
        }
        inline float GetFPS() const
        {
            return isPaused ? 0 : fps;
        }

    private:
        float fps;
        unsigned int interval; // Milliseconds
        std::atomic<bool> isPaused {false};
        std::atomic<bool> isRunning {false};

        std::function<void()> func;
    };
}

#endif
