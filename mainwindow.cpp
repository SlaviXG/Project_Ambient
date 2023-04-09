#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GameController.h"



MainWindow::MainWindow(EnvironmentScene* scene, QWidget *parent)
    : QMainWindow(parent), scene(scene)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(this->ui->horizontalLayoutWidget);

    ui->environmentView->setScene(scene);

    /*EnvironmentScene* scene = new EnvironmentScene();

    CellView* cell = new CellView(ui->environmentView->width() / 2, ui->environmentView->height() / 2, 20, 20);
    scene->addCell(cell);
    ui->environmentView->setScene(scene);

    // Move example
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [cell]() {
        cell->moveBy(1, 2);
        qDebug() << "Move\n";
    });
    timer->start(10);*/
}

qreal MainWindow::getEnvironmentWidth() const {
    return ui->environmentView->width();
}

qreal MainWindow::getEnvironmentHeight() const {
    return ui->environmentView->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initEnvironmentSize() {
    // Get the size of the viewport
    QSize viewportSize = ui->environmentView->viewport()->size();

    // Set the scene rect to the same size as the viewport
    scene->setSceneRect(QRectF(QPointF(0, 0), viewportSize));

    // Update the view
    ui->environmentView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    this->initEnvironmentSize();
}
