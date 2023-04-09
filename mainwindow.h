#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <EnvironmentScene.h>

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

    void inline setController(controller::GameInteractor*  controller) {this->controller = controller; };

    /**
     * @brief Updates items' view location
     */
    void updateEnvironment();

public slots:
    /**
     * @brief Scales up environment view size
     */
    void initEnvironmentSize();

private:
    Ui::MainWindow *ui;
    EnvironmentScene* scene;
    controller::GameInteractor* controller = nullptr;

    void resizeEvent(QResizeEvent* event) override;
};
#endif // MAINWINDOW_H
