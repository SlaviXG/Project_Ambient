#include "../include/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <memory>

#include "../include/configs/Configuration.h"
#include "../include/configs/ConfigurationChain.h"
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

    ConfigurationChain chain;

    //environment::EnvironmentDecorator env(10000, 10000); env.setLogger(std::unique_ptr<Logger>(new ConsoleLogger()));
    genepool::GenePool pool(cell_num);
    environment::Environment env(0, 0, nullptr, &pool);
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

    chain.addHandler(&env);
    chain.addHandler(&cont);

    Configuration configs("configs.json");
    chain.loadConfiguration(configs);

    cont.setConfigs(&chain, &configs);
    
    env.setCellInteractor(&cont);
    win.setController(&cont);

    win.setWindowTitle("Project Ambient");
    win.show();
    cont.setCellTracker(win.getCellTracker());

    win.initEnvironmentSize();
    cont.start();

    chain.saveConfiguration(configs);
    configs.save();

    return a.exec();
}
