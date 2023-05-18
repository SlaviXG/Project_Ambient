#include "mainwindow.h"

#include <QApplication>

#include "GameController.h"
#include "Environment.h"
#include "logger.h"
#include "genepool.h"
#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "test_tick.hpp"
#include "test_environment.hpp"

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
    unsigned int cell_num = 15;
    QApplication a(argc, argv);
    genepool::GenePool pool(cell_num);
    environment::Environment env(200, 200, nullptr, &pool);
    EnvironmentScene scene;
    MainWindow win(&scene);;
    controller::GameController cont(&win, &scene, &env);
    cont.AddLogger(new ConsoleLogger());
    cont.AddLogger(new FileLogger("logs.txt"));
    env.setCellInteractor(&cont);
    win.setController(&cont);
    win.show();

    win.initEnvironmentSize();
    env.generateCells(cell_num/*, &cont*/);
    /*cont.addCell({0, 0});
        cont.addCell({60, 50});
        cont.addCell({30, 75});
        cont.addCell({70, 76});
        cont.addCell({31, 65});
        cont.addCell({23, 83});
        cont.addCell({68, 22});
        cont.addCell({52, 24});
        cont.addCell({23, 23});
        cont.addCell({93, 11});
        cont.addCell({90, 64});
        cont.addCell({84, 34});
        cont.addCell({55, 22});
        cont.addCell({18, 43});*/


    cont.start();
    return a.exec();
}
