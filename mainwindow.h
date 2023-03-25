#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace controller { class GameController; }

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    qreal getWidth() const;
    qreal getHeight() const;

private:
    Ui::MainWindow *ui;
    controller::GameController* controller = nullptr;
    
};
#endif // MAINWINDOW_H
