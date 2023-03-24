#include "EnvironmentScene.h"

EnvironmentScene::EnvironmentScene(QObject *parent)
    : QGraphicsScene(parent)
{
    bool colorGradationsLoaded = this->loadColorGradations();
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
        successfully = successfully & currentGradation.load("color_gradient_" + QString::number(i));
        currentGradation.scaledToHeight(20, Qt::SmoothTransformation);
        this->cellColorGradations.append(currentGradation);
    }

    return successfully;
}
