#ifndef RENDERINGTHREAD_H
#define RENDERINGTHREAD_H

#include <QThread>
#include "GameController.h"

class RenderingThread : public QThread {
    Q_OBJECT
    controller::GameController* gameController;
public:
    RenderingThread(controller::GameController* controller)
        : gameController(controller) {}
    void run() override {
        gameController->render();
        emit renderingCompleted();
    }

signals:
    void renderingCompleted();
};


#endif // RENDERINGTHREAD_H
