#ifndef GAMELOGICTHREAD_H
#define GAMELOGICTHREAD_H

#include <deque>
#include <functional>

#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#include "GameController.h"

constexpr size_t kMaxTaskCount = 1000000;

/**
 * @class GameLogicThread
 * @brief A thread class responsible for executing game logic tasks.
 */
class GameLogicThread : public QThread {
    Q_OBJECT
    controller::GameController* gameController; ///< Pointer to the GameController instance.
    std::deque<std::function<void()>> tasks; ///< A deque to store the tasks.
    QMutex mutex; ///< A mutex to ensure thread safety.
public:
    /**
     * @brief Constructs a GameLogicThread object with a given GameController instance.
     * @param controller The GameController instance.
     */
    GameLogicThread(controller::GameController* controller)
        : gameController(controller) {}

    /**
     * @brief Adds a task to the task queue.
     * @param task The task to be added.
     */
    void queueTask(std::function<void()> task) {
        QMutexLocker locker(&mutex);
        tasks.push_back(task);
    }

    /**
     * @brief Clears all the tasks from the task queue.
     */
    void clearTasks() {
        QMutexLocker locker(&mutex);
        tasks.clear();
    }

    /**
     * @brief Runs the game logic thread.
     *        The thread keeps executing tasks until interruption is requested.
     *        If there are no tasks, the thread sleeps for a short period.
     */
    void run() override {
        while (!isInterruptionRequested()) {
            std::function<void()> task = nullptr;
            {
                QMutexLocker locker(&mutex);
                if (!tasks.empty()) {
                    task = tasks.front();
                    tasks.pop_front();
                }
            }

            if (task != nullptr) {
                task();
                emit logicCompleted();
            } else {
                QThread::msleep(10);
            }

            if (tasks.size() > kMaxTaskCount) {
                clearTasks();
            }
        }
    }

signals:
    /**
     * @brief Signal emitted when a logic task is completed.
     */
    void logicCompleted();
};

#endif // GAMELOGICTHREAD_H
