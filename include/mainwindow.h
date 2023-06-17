/**
 * @file MainWindow.h
 * @brief Header file for the MainWindow class
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EnvironmentScene.h"
#include "celltracker.h"

namespace controller { class GameInteractor; }

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Class for the main window of the application.
 *
 * The MainWindow class is responsible for managing the main window 
 * and interacting with user input.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param scene The environment scene to display in the main window.
     * @param parent The parent widget.
     */
    MainWindow(EnvironmentScene* scene, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

    /**
     * @brief Gets the width of the environment view.
     * @return The width of the environment view.
     */
    qreal getEnvironmentWidth() const;

    /**
     * @brief Gets the height of the environment view.
     * @return The height of the environment view.
     */
    qreal getEnvironmentHeight() const;

    /**
     * @brief Gets the cell tracker.
     * @return The cell tracker.
     */
    CellTracker* getCellTracker();

    /**
     * @brief Sets the controller for the main window.
     * @param controller The controller to set.
     */
    void setController(controller::GameInteractor*  controller);

    /**
     * @brief Updates the environment view.
     */
    void updateEnvironment();

    /**
     * @brief Gets the number of cells to add.
     * @return The number of cells to add.
     */
    std::size_t getCellCountToAdd() const;

    /**
     * @brief Sets the current cell count label.
     * @param n The value to set.
     */
    void setCurrentCellCountLabel(size_t n);

public slots:
    /**
     * @brief Initializes the size of the environment view.
     */
    void initEnvironmentSize();

signals:
    /**
     * @brief Signal that is emitted when the add cells button is clicked.
     */
    void on_add_cells_Button_clicked_signal();

private slots:
    // Private slot functions for handling different button clicks.
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_restartButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void on_add_cells_Button_clicked();
    void on_cell_clicked();
    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    EnvironmentScene* scene;
    controller::GameInteractor* controller = nullptr;
    QGraphicsScene cellDemoScene;
    CellTracker* cellTracker;

    /**
     * @brief Resizes the main window.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent* event) override;
};
#endif // MAINWINDOW_H
