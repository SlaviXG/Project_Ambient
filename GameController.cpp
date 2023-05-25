#include "GameController.h"

#include <utility>

#include <QApplication>
#include <QCoreApplication>

#include "GameLogicThread.h"


controller::GameController::GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment)
    : view(view), scene(scene), environment(environment), timer(this), loggers(), logicThread(new GameLogicThread(this)), collector(scene) {
    connect(logicThread, &GameLogicThread::logicCompleted, this, &GameController::render);
    connect(view, &MainWindow::on_add_cells_Button_clicked_signal, this, &GameController::GenerateRandomCellsSlot);
    //connect(view, &MainWindow::resizeSignal, this, &GameController::render);
}

controller::GameController::~GameController(){
    this->stop();
    view->hide();
    QThread::msleep(10000); // wait until worker thread removes all cells
    this->logicThread->exit();
};

void controller::GameController::addCell(environment::Cell* cellptr)
{
    //QMutexLocker locker(&mutex);

    auto point = cellptr->getPosition();

    double x = point.i * view->getEnvironmentWidth() / environment->getWidth();
    double y = point.j * view->getEnvironmentHeight() / environment->getHeight();
    auto cellViewptr = scene->genCellViewPtr(x, y, kCellSize, kCellSize, cellptr->getAggressiveness() * 100);
    // scene->addCell(cellViewptr);

    NotifyLoggers("Cell  " + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) +
                  "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } ""  was added ");

    /*NotifyLoggers("Cell's (" + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) + ") position: Environment {" +
                  std::to_string(cellptr->getPosition().i) + ", " + std::to_string(cellptr->getPosition().j) + "}" +
                  ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}");*/

    cellMap.insert({cellptr, cellViewptr});
}


void controller::GameController::removeCell(environment::Cell *cell)
{
    Q_ASSERT(cellMap.find(cell) != cellMap.end());

    // Add CellView pointer into remove list to delete it from the GUI thread
    collector.append(cellMap.at(cell));
    cellMap.erase(cell);

    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + "  { " + std::to_string(cell->getPosition().i) + ", " + std::to_string(cell->getPosition().j) + " } " + " was removed");
}

void controller::GameController::start()
{
    timer.disconnect();
    this->logicThread->start();

    logicThread->queueTask([this]() { this->GenerateRandomCells(kStartingCellCount); });

    connect(&timer, &QTimer::timeout, this, &GameController::executeLogicThread);
    timer.start(1000 / kFps);
}

void controller::GameController::executeLogicThread() {
    if (logicThread->isRunning()) {
        logicThread->queueTask([this]() { this->processAI(); });
    }
}

void controller::GameController::GenerateRandomCellsSlot() {
    logicThread->clearTasks();
    logicThread->queueTask([this]() { this->GenerateRandomCells(view->getCellCountToAdd()); });
}

void controller::GameController::stop()
{
    this->pause();

    auto cells = environment->getCells();

    this->logicThread->queueTask([cells = std::move(cells), environment = environment]() {
        for (const auto& cell : cells)
        {
            environment->InvalidateCell(cell);
            environment->RemoveCell(cell);
        }
    });
}

void controller::GameController::pause()  {
    timer.stop();
    this->logicThread->requestInterruption();
    this->logicThread->wait();
    this->logicThread->clearTasks();
    QApplication::processEvents();
}
void controller::GameController::resume()  {
    timer.start(1000 / kFps);
    this->logicThread->start();
}

// Works in the Worker thread
void controller::GameController::processAI()
{
    auto cells = environment->getCells();

    for (auto cell : cells)
    {
        if (cell->isAlive())
        {
        std::string address = std::to_string(reinterpret_cast<std::uintptr_t>(cell));

        environment::actions action = cell->act();

        auto point = cell->getPosition();

        switch (action) {
        case environment::kMoveUp:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " moved");
            break;
        case environment::kPhotosynthesis:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " photosynthesized");
            break;
        case environment::kDuplication:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " duplicated");
            break;
        case environment::kAttackUp:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " +  " attacked");
            break;
        case environment::kCellIsDead:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " dead");
            break;
        default:
            NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " did magic");
            break;
        }
         NotifyLoggers("Cell " + address + "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } " + " total score is:" + std::to_string(cell->getTotalScore()));
        }

        if(cell->isAlive() == false)
        {
            environment->RemoveCell(cell);
        }
    }
    NotifyLoggers("Cells remained: " + std::to_string(environment->getCellNumber()));
};


void controller::GameController::render()
{
    // Removes CellView objects that have been deleted from the Logic thread
    collector.clear();

    // Checks if we are in a GUI thread
    Q_ASSERT(qApp->thread() == QThread::currentThread());


    auto cells = environment->getCells();

    NotifyLoggers("Cells to render: " + std::to_string(environment->getCellNumber()));

    double scaleW = (view->getEnvironmentWidth() - kViewPadding) / environment->getWidth();
    double scaleH = (view->getEnvironmentHeight() - kViewPadding) / environment->getHeight();

    for (const auto &cell : cells)
    {
        auto point = cell->getPosition();
        double x = point.i * scaleW;
        double y = point.j * scaleH;

        /* NotifyLoggers("Cell's " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " position: Environment {" +
                      std::to_string(cell->getPosition().i) + ", " + std::to_string(cell->getPosition().j) + "}" +
                      ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}"); */

        // If the worker thread deleted a cell during the loop execution
        if (cellMap.find(cell) == cellMap.end())
            continue;

        CellView* cellView = cellMap.at(cell);

        assert(cellView != nullptr);

        // Check if the cell has been added to the scene, since AddCell
        // changes the state of the GameController and Environment only from the worker thread.
        // We could change the state of the GUI only from the UI thread (1)
        if (!scene->contains(cellView))
            scene->addCell(cellView);

        scene->updateCell(cellView, x, y, cell->getAggressiveness() * 100);
    }

    view->setCurrentCellCountLabel(environment->getCellNumber());
    scene->update();
};
