#ifndef ENVIRONMENT_SCENE_H
#define ENVIRONMENT_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QSet>
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

    CellView* genCellViewPtr(qreal x, qreal y, int width, int height, int colorGrad);
    void addCell(CellView* cell);
    void removeCell(CellView* cell);
    void updateCell(CellView* cell, qreal x, qreal y, int colorGrad);
    const QList<CellView*>& getCells() const;
    bool contains(CellView* cellptr) const;

private:
    QList<CellView*> cells;
    QSet<CellView*> cellSet; // used for fast O(1) checking for an element instead of O(n) when using qlist
    QVector <QPixmap> cellColorGradations;
    bool colorGradationsLoaded;

    bool loadColorGradations();  
};
#endif // ENVIRONMENT_SCENE_H
