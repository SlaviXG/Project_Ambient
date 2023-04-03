#include "mainwindow.h"

#include <QApplication>

#include "GameController.h"
#include "Environment.h"
#include "logger.h"

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
    cont.AddLogger(new ConsoleLogger());
    cont.AddLogger(new FileLogger("logs.txt"));
    env.setCellInteractor(&cont);
    win.setController(&cont);
    cont.start();
    win.show();
    cont.addCell({50, 50});
    cont.addCell({12, 50});
    cont.addCell({30, 75});
    /*cont.addCell({90, 76});
    cont.addCell({3, 65});
    cont.addCell({23, 83});
    cont.addCell({98, 12});
    cont.addCell({52, 24});
    cont.addCell({23, 23});
    cont.addCell({93, 11});
    cont.addCell({90, 64});
    cont.addCell({84, 34});
    cont.addCell({55, 22});
    cont.addCell({18, 43});*/

    /*cont.addCell({54, 25});
    cont.addCell({94, 23});
    cont.addCell({62, 72});
    cont.addCell({92, 8});
    cont.addCell({5, 23});
    cont.addCell({3, 23});
    cont.addCell({2, 83});
    cont.addCell({54, 74});
    cont.addCell({90, 15});
    cont.addCell({13, 11});
    cont.addCell({80, 44});
    cont.addCell({74, 34});
    cont.addCell({69, 21});
    cont.addCell({38, 43});*/

    /*cont.addCell({54, 25});
    cont.addCell({94, 23});
    cont.addCell({62, 72});
    cont.addCell({92, 8});
    cont.addCell({5, 23});
    cont.addCell({3, 23});
    cont.addCell({2, 83});
    cont.addCell({54, 74});
    cont.addCell({90, 15});
    cont.addCell({13, 11});
    cont.addCell({80, 44});
    cont.addCell({74, 34});
    cont.addCell({69, 21});
    cont.addCell({38, 43});*/

    return a.exec();
}
