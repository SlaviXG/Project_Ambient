#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

#include "EnvironmentScene.h"
#include "CellView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(this->ui->horizontalLayoutWidget);

    EnvironmentScene* scene = new EnvironmentScene();

    CellView* cell = new CellView(ui->environmentView->width() / 2, ui->environmentView->height() / 2, 20, 20);
    scene->addCell(cell);
    ui->environmentView->setScene(scene);

    // Move example
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [cell]() {
        cell->moveBy(1, 2);
        qDebug() << "Move\n";
    });
    timer->start(10);
}

qreal MainWindow::getWidth() const {
    return ui->environmentView->width();
}

qreal MainWindow::getHeight() const {
    return ui->environmentView->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}
