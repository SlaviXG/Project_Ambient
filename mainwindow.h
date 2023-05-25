#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <EnvironmentScene.h>
#include <celltracker.h>

namespace controller { class GameInteractor; }

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(EnvironmentScene* scene, QWidget *parent = nullptr);
    ~MainWindow();

    qreal getEnvironmentWidth() const;
    qreal getEnvironmentHeight() const;

    CellTracker* getCellTracker();

    void setController(controller::GameInteractor*  controller);

    /**
     * @brief Updates items' view location
     */
    void updateEnvironment();

    /**
     * @brief GetCellCountToAdd
     * @return Value of the LineEdit "cell_to_add_LineEdit"
     */
    std::size_t getCellCountToAdd() const;
    void setCurrentCellCountLabel(size_t n);



public slots:
    /**
     * @brief Scales up environment view size
     */
    void initEnvironmentSize();

signals:
    void on_add_cells_Button_clicked_signal();

private slots:
    void on_restartButton_clicked();

    void on_pauseButton_clicked();

    void on_resumeButton_clicked();

    // void on_pushButton_clicked() {};

    void on_add_cells_Button_clicked();

    void on_cell_clicked();

private:
    Ui::MainWindow *ui;
    EnvironmentScene* scene;
    controller::GameInteractor* controller = nullptr;
    QGraphicsScene cellDemoScene;
    CellTracker cellTracker;

    void resizeEvent(QResizeEvent* event) override;
};
#endif // MAINWINDOW_H
