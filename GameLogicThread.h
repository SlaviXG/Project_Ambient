#ifndef GAMELOGICTHREAD_H
#define GAMELOGICTHREAD_H

#include <deque>
#include <functional>

#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#include "GameController.h"

constexpr size_t kMaxTaskCount = 1000000;

class GameLogicThread : public QThread {
    Q_OBJECT
    controller::GameController* gameController;
    std::deque<std::function<void()>> tasks;
    QMutex mutex;
public:
    GameLogicThread(controller::GameController* controller)
        : gameController(controller) {}
    void queueTask(std::function<void()> task) {
        QMutexLocker locker(&mutex);
        tasks.push_back(task);
    }

    void clearTasks() {
        QMutexLocker locker(&mutex);
        tasks.clear();
    }

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
            qDebug() << "Task number:" << tasks.size();
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
    void logicCompleted();
};


#endif // GAMELOGICTHREAD_H
