#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include <functional>
#include <QTimer>
#include <QObject>

/**
 * @class Debouncer
 * @brief A class that implements the Debounce pattern to delay the execution of a function.
 *
 * The Debouncer class provides a mechanism to delay or throttle the execution of a given function
 * until a certain amount of time has passed without it being called again. It is commonly used to
 * prevent rapid or frequent invocations of a function.
 */
class Debouncer : public QObject {
    Q_OBJECT

public:
    /**
     * Constructs a Debouncer object with the specified delay.
     * @param delay The delay in milliseconds between subsequent invocations of the debounced function.
     */
    explicit Debouncer(int delay) : delay(delay) {}
    virtual ~Debouncer() override {}

    /**
     * Schedules the invocation of a function, debouncing subsequent calls within the specified delay.
     * @tparam Func The type of the function or callable object.
     * @tparam Args The types of the arguments passed to the function.
     * @param func The function or callable object to be invoked after the debounce delay.
     * @param args The arguments to be passed to the function.
     *
     * The debounced function will be called only once, after the specified delay has elapsed and no
     * subsequent invocations have occurred within that time. Any previous pending invocation will be
     * canceled.
     */
    template<typename Func, typename... Args>
    void debounce(Func&& func, Args&&... args) {
        // Cancel any previous pending invocation
        if (timer.isActive()) {
            timer.stop();
        }

        // Schedule the new invocation
        std::function<void()> callback = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        timer.setSingleShot(true);
        timer.start(delay);

        // Connect the timeout signal to the slot
        connect(&timer, &QTimer::timeout, this, [this, callback]() {
            handleTimeout(callback);
        });
    }

    void setDelay(int delay) {this->delay = delay;}

private slots:
    void handleTimeout(std::function<void()> callback) {
        callback();
    }

private:
    QTimer timer;
    int delay;
};

#endif // DEBOUNCER_H
