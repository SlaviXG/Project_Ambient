#include "mainwindow.h"

#include <QApplication>
#include <QTest>

#include "test_environment.h"

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Test_Environment, argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
