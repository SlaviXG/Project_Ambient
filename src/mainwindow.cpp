#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include "../include/GameController.h"



MainWindow::MainWindow(EnvironmentScene* scene, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(scene),
    cellDemoScene(this)
{
    ui->setupUi(this);
    this->setCentralWidget(this->ui->horizontalLayoutWidget);

    ui->environmentView->setScene(scene);

    this->ui->cellDemo->setScene(&this->cellDemoScene);
    this->cellDemoScene.setSceneRect(-5, -5, this->ui->cellDemo->width() - 5, this->ui->cellDemo->width() - 5);
    cellTracker = new CellTracker(&cellDemoScene, this->ui->curEnergyLabel, this->ui->aggressiveness, this->scene);

    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::on_startButton_clicked);
    connect(ui->actionPause, &QAction::triggered, this, &MainWindow::on_pauseButton_clicked);
    connect(ui->actionResume, &QAction::triggered, this, &MainWindow::on_resumeButton_clicked);
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::on_stopButton_clicked);
    connect(ui->actionRestart, &QAction::triggered, this, &MainWindow::on_restartButton_clicked);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionOpen_Settings, &QAction::triggered, this, &MainWindow::on_settingsButton_clicked);
}

void MainWindow::setController(controller::GameInteractor*  controller) {
    this->controller = controller;
};


qreal MainWindow::getEnvironmentWidth() const {
    return ui->environmentView->width();
}

qreal MainWindow::getEnvironmentHeight() const {
    return ui->environmentView->height();
}

CellTracker *MainWindow::getCellTracker()
{
    return this->cellTracker;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cellTracker;
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

void MainWindow::on_resumeButton_clicked()
{
    controller->resume();
    qDebug() << "Resume";
}

void MainWindow::on_startButton_clicked()
{
    controller->start();
    qDebug() << "start";
}

void MainWindow::on_stopButton_clicked()
{
    controller->stop();
    qDebug() << "stop";
}

void MainWindow::on_pauseButton_clicked()
{
    controller->pause();
    qDebug() << "Pause";
}

void MainWindow::on_restartButton_clicked()
{
    controller->stop();
    controller->start();
    qDebug() << "Restart";
}

void MainWindow::on_add_cells_Button_clicked()
{
    emit on_add_cells_Button_clicked_signal();
}

void MainWindow::on_cell_clicked()
{
    //TODO: ui->cellDemo->
}

std::size_t MainWindow::getCellCountToAdd() const
{
    return ui->cell_to_add_LineEdit->text().toULongLong();
}

void MainWindow::setCurrentCellCountLabel(size_t n)
{
    ui->cell_count_Label->setText(QString::number(static_cast<qulonglong>(n)));
}

void MainWindow::on_settingsButton_clicked()
{
    controller->openSettingsWindow();
}


