#include "mainwindow.h"

#include <QApplication>

#include "GameController.h"
#include "Environment.h"
#include "logger.h"

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "test_tick.hpp"
#include "test_environment.hpp"

void gen_cells(int N, controller::GameController *cont, environment::Environment *env){
    for(int i = 0; i < N ; i++){
        Point point = env->getRandomFreePosOnMap();
        if(point.i != -1){
            cont->addCell(point);
        }
        else{
            continue;
        }
    }
}



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

    QApplication a(argc, argv);

    environment::Environment env(2000, 2000);
    EnvironmentScene scene;
    MainWindow win(&scene);;
    controller::GameController cont(&win, &scene, &env);
    cont.AddLogger(new ConsoleLogger());
    cont.AddLogger(new FileLogger("logs.txt"));
    env.setCellInteractor(&cont);
    win.setController(&cont);
    win.show();

    win.initEnvironmentSize();
    gen_cells(100, &cont, &env);
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
