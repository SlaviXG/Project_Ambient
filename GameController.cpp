#include "GameController.h"


void controller::GameController::addCell(environment::Cell* cellptr)
{
    auto point = cellptr->getPosition();

    double x = point.i * view->getEnvironmentWidth() / environment->getWidth();
    double y = point.j * view->getEnvironmentHeight() / environment->getHeight();
    auto cellViewptr = scene->genCellViewPtr(x, y, kCellSize, kCellSize, cellptr->getAggressiveness() * 100);
    scene->addCell(cellViewptr);

    NotifyLoggers("Cell  " + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) +
                  "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } ""  was added ");

    /*NotifyLoggers("Cell's (" + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) + ") position: Environment {" +
                  std::to_string(cellptr->getPosition().i) + ", " + std::to_string(cellptr->getPosition().j) + "}" +
                  ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}");*/

    cellMap.insert({cellptr, cellViewptr});
}


void controller::GameController::removeCell(environment::Cell *cell)
{
    assert(cellMap.find(cell) != cellMap.end());

    this->scene->removeCell(cellMap.at(cell));
    cellMap.erase(cell);

    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + "  { " + std::to_string(cell->getPosition().i) + ", " + std::to_string(cell->getPosition().j) + " } " + " was removed");
}


void controller::GameController::processAI()
{
    std::vector<environment::Cell*> cells = environment->getCells();



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
    view->setCurrentCellCountLabel(environment->getCellNumber());
};


void controller::GameController::render()
{
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

        CellView* cellView = cellMap.at(cell);

        assert(cellView != nullptr);
        scene->updateCell(cellView, x, y, cell->getAggressiveness() * 100);
    }
};
