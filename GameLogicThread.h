#ifndef GAMELOGICTHREAD_H
#define GAMELOGICTHREAD_H

#include <QThread>
#include "GameController.h"

class GameLogicThread : public QThread {
    Q_OBJECT
    controller::GameController* gameController;
public:
    GameLogicThread(controller::GameController* controller)
        : gameController(controller) {}
    void run() override {
        gameController->processAI();
        emit logicCompleted();
    }

signals:
    void logicCompleted();
};

#endif // GAMELOGICTHREAD_H
