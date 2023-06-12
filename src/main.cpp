#include "../include/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <memory>

#include "../include/GameController.h"
#include "../include/Environment.h"
#include "../include/logger.h"
#include "../include/genepool.h"

#define DOCTEST_CONFIG_IMPLEMENT

#include "../tests/doctest.h"
#include "../tests/test_environment.hpp"

#include "../include/EnvironmentDecorator.h"
#include "../include/GameControllerDecorator.h"


int main(int argc, char *argv[])
{
    srand(time(0));
    // Unit tests
//#ifdef _DEBUG
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit()) {
    return res;
    }
//#endif // _DEBUG
    unsigned int cell_num = 100;
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/resources/cell_color_gradations/resources/icon.ico"));
    QApplication::setApplicationName("Project Ambient");

    //environment::EnvironmentDecorator env(10000, 10000); env.setLogger(std::unique_ptr<Logger>(new ConsoleLogger()));
    genepool::GenePool pool(cell_num);
    environment::Environment env(1000, 1000, nullptr, &pool);
    EnvironmentScene scene;
    MainWindow win(&scene);
    controller::GameController cont(&win, &scene, &env);
    //controller::GameControllerDecorator cont(&win, &scene, &env);
    //cont.AddLogger(new ConsoleLogger());
    //cont.AddLogger(new FileLogger("logs.txt"));

    QFile file(":/resources/cell_color_gradations/resources/SyNet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    win.setStyleSheet(styleSheet);
    a.setStyleSheet(styleSheet);
    
    env.setCellInteractor(&cont);
    win.setController(&cont);

    win.setWindowTitle("Project Ambient");
    win.show();
    cont.setCellTracker(win.getCellTracker());

    win.initEnvironmentSize();
    cont.start();
    return a.exec();
}
