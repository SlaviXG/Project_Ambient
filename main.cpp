//#include "mainwindow.h"

//#include <QApplication>

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
//#include "test_environment.hpp"
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

    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
