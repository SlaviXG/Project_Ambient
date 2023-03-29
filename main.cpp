#include "mainwindow.h"

#include <QApplication>

#include "GameController.h"
#include "Environment.h"

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "test_tick.hpp"
#include "test_environment.hpp"


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

    environment::Environment env(100, 100);
    EnvironmentScene scene;
    MainWindow win(&scene);;
    controller::GameController cont(&win, &scene, &env);
    env.setCellInteractor(&cont);
    win.setController(&cont);
    // cont.addCell({50, 50});
    cont.start();
    win.show();

    return a.exec();
}
