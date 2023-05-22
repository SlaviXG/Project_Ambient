#include "mainwindow.h"

#include <QApplication>
#include <memory>

#include "GameController.h"
#include "Environment.h"
#include "logger.h"

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "test_environment.hpp"

#include "EnvironmentDecorator.h"
#include "GameControllerDecorator.h"


int main(int argc, char *argv[])
{
    // Unit tests
//#ifdef _DEBUG
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit()) {
    return res;
    }
//#endif // _DEBUG

    QApplication a(argc, argv);

    environment::Environment env(10000, 10000);
    //environment::EnvironmentDecorator env(10000, 10000); env.setLogger(std::unique_ptr<Logger>(new ConsoleLogger()));
    EnvironmentScene scene;
    MainWindow win(&scene);;
    controller::GameController cont(&win, &scene, &env);
    //controller::GameControllerDecorator cont(&win, &scene, &env);
    //cont.AddLogger(new ConsoleLogger());
    //cont.AddLogger(new FileLogger("logs.txt"));
    env.setCellInteractor(&cont);
    win.setController(&cont);
    win.show();

    win.initEnvironmentSize();

    cont.start();
    return a.exec();
}
