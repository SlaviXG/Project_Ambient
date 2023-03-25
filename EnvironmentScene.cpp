#include "EnvironmentScene.h"
#include <iostream>

EnvironmentScene::EnvironmentScene(QObject *parent)
    : QGraphicsScene(parent)
{
    this->cellColorGradations = new QVector <QImage>;
    this->colorGradationsLoaded = this->loadColorGradations();
    std::cout << "Color gradations are " << (colorGradationsLoaded ? ("") : ("not ")) << "loaded." << std::endl;
}

EnvironmentScene::~EnvironmentScene()
{

}

bool EnvironmentScene::loadColorGradations()
{
    bool successfully = true;

    for(int i = 0; i < 100; i++)
    {
        QImage currentGradation;
        successfully = successfully & currentGradation.load(":/resources/cell_color_gradations/resources/cell_color_gradations/color_gradient_" + QString::number(i) + ".png");
        std::cout << QString::number(i).toStdString() << std::endl;
        currentGradation = currentGradation.scaledToWidth(20, Qt::SmoothTransformation);
        this->cellColorGradations->push_back(currentGradation);
    }

    return successfully;
}
