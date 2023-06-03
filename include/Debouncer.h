#include <chrono>
#include <thread>
#include <functional>

/**
 * @class Debouncer
 * @brief A class that provides a debounce functionality.
 *
 * This class provides a way to ensure that a function or method is not called
 * more frequently than a specified timeout. This can be useful in scenarios
 * where a function is triggered by an event that can occur rapidly (such as a
 * button press), but the function itself should not be executed too frequently.
 */
class Debouncer {
public:
    /**
     * @brief Construct a new Debouncer object.
     *
     * @param timeout The minimum time interval between function calls.
     */
    Debouncer(std::chrono::milliseconds timeout) : timeout(timeout), last_call(std::chrono::steady_clock::now() - timeout) {}

    /**
     * @brief Call a function if enough time has passed since the last call.
     *
     * This method will call the provided function with the provided arguments
     * if enough time has passed since the last call to this method. The time
     * interval is specified by the `timeout` parameter passed to the
     * constructor.
     *
     * @tparam Callable The type of the function to call.
     * @tparam Args The types of the arguments to pass to the function.
     * @param func The function to call.
     * @param args The arguments to pass to the function.
     */
    template<typename Callable, typename... Args>
    void debounce(Callable&& func, Args&&... args) {
        auto now = std::chrono::steady_clock::now();
        if(now - last_call >= timeout) {
            std::forward<Callable>(func)(std::forward<Args>(args)...);
            last_call = now;
        }
    }

private:
    std::chrono::milliseconds timeout;  ///< The minimum time interval between function calls.
    std::chrono::steady_clock::time_point last_call;  ///< The time point of the last function call.
};
