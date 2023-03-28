#ifndef ENVIRONMENT_SCENE_H
#define ENVIRONMENT_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>
#include <QImage>

#include "CellView.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EnvironmentScene; }
QT_END_NAMESPACE

class EnvironmentScene : public QGraphicsScene
{
public:
    EnvironmentScene(QObject *parent = nullptr);
    ~EnvironmentScene();

    void addCell(CellView* cell, int colorGrad);
    void removeCell(CellView* cell);
    void updateCell(CellView* cell, int x, int y, int colorGrad);
    const QList<CellView*>& getCells() const;

private:
    QList<CellView*> cells;
    QVector <QPixmap> cellColorGradations;
    bool colorGradationsLoaded;

    bool loadColorGradations();  
};
#endif // ENVIRONMENT_SCENE_H
