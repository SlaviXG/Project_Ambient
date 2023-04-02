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
        }
    }
    // Removal of dead cells
    cells = environment->getCells();
    for (auto cell : cells)
    {
        if (!cell->isAlive())
            environment->RemoveCell(cell);
    }
};


void controller::GameController::render()
{
    auto cells = environment->getCells();
    for (const auto &cell : cells)
    {
        auto point = cell->getPosition();
        double x = point.i * view->getEnvironmentWidth() / environment->getWidth();
        double y = point.j * view->getEnvironmentHeight() / environment->getHeight();

        /* NotifyLoggers("Cell's " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " position: Environment {" +
                      std::to_string(cell->getPosition().i) + ", " + std::to_string(cell->getPosition().j) + "}" +
                      ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}"); */

        CellView* cellView = cellMap.at(cell);

        assert(cellView != nullptr);
        scene->updateCell(cellView, x, y, cell->getAggressiveness() * 100);
    }
};
