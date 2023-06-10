#include "../include/EnvironmentScene.h"

#include <iostream>

#include "../include/GameController.h"

EnvironmentScene::EnvironmentScene(QObject *parent)
    : QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::transparent);
    this->colorGradationsLoaded = this->loadColorGradations();
    std::cout << "Color gradations are " << (colorGradationsLoaded ? ("") : ("not ")) << "loaded." << std::endl;

    // this->addCell(this->genCellViewPtr(500, 500, 20, 20, 99));
}

EnvironmentScene::~EnvironmentScene()
{
}

CellView *EnvironmentScene::genCellViewPtr(qreal x, qreal y, int width, int height, int colorGrad)
{
    colorGrad = colorGrad % 100;
    CellView* cell = new CellView(x, y, width, height, &(this->cellColorGradations[colorGrad]));
    return cell;
}

void EnvironmentScene::addCell(CellView *cell)
{
    cells.append(cell);
    cellSet.insert(cell);
    this->addItem(cell);
}

void EnvironmentScene::removeCell(CellView *cell)
{
    this->removeItem(cell);
    this->cells.removeOne(cell);
    this->cellSet.remove(cell);
    delete cell;
}

bool EnvironmentScene::contains(CellView* cellptr) const {
    return cellSet.contains(cellptr);
}


void EnvironmentScene::updateCell(CellView *cell, qreal x, qreal y, int colorGrad)
{
    cellSet.remove(cell);
    colorGrad = colorGrad % 100;
    cell->updateCellView(x, y, &(this->cellColorGradations[colorGrad]));
    cellSet.insert(cell);
}

bool EnvironmentScene::loadColorGradations()
{
    bool successfully = true;

    for(int i = 0; i < 100; i++)
    {
        QImage currentGradation;
        successfully = successfully & currentGradation.load(":/resources/cell_color_gradations/resources/cell_color_gradations/color_gradient_" + QString::number(i) + ".png", "PNG");
        currentGradation = currentGradation.scaledToWidth(controller::cellSize, Qt::SmoothTransformation);
        QPixmap imagePixmap = QPixmap::fromImage(currentGradation);
        this->cellColorGradations.push_back(imagePixmap);
        std::cout << QString::number(i).toStdString() << std::endl;
    }

    return successfully;
}
