QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CellView.cpp \
    src/Environment.cpp \
    src/EnvironmentScene.cpp \
    src/GameController.cpp \
    src/Genotype.cpp \
    src/cell.cpp \
    src/celltracker.cpp \
    src/frame.cpp \
    src/genepool.cpp \
    src/main.cpp \
    src/mainwindow.cpp \

HEADERS += \
    include/CellView.h \
    include/Debouncer.h \
    include/celltracker.h \
    include/CellViewGarbageCollector.h \
    include/GameLogicThread.h \
    include/EnvironmentDecorator.h \
    include/GameControllerDecorator.h \
    include/genepool.h \
    include/logger.h \
    include/point.h \
    include/Environment.h \
    include/EnvironmentScene.h \
    include/GameController.h \
    include/Genotype.h \
    include/Matrix.h \
    include/cell.h \
    tests/doctest.h \
    include/frame.h \
    include/mainwindow.h \
    tests/test_Genotype.hpp \
    tests/test_environment.hpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
