cmake_minimum_required(VERSION 3.16)

# project name
project(Project_Ambient)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to Qt6 installation directory
set(CMAKE_PREFIX_PATH "C:/Qt/6.3.2/mingw_64")

# find Qt packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# list your sources, headers, forms, and resources files
set(SOURCES
    src/CellView.cpp
    src/Environment.cpp
    src/EnvironmentScene.cpp
    src/GameController.cpp
    src/Genotype.cpp
    src/cell.cpp
    src/celltracker.cpp
    src/frame.cpp
    src/genepool.cpp
    src/main.cpp
    src/mainwindow.cpp
    resources.rc
)
set(HEADERS
    include/CellView.h
    include/Debouncer.h
    include/celltracker.h
    include/CellViewGarbageCollector.h
    include/GameLogicThread.h
    include/EnvironmentDecorator.h
    include/GameControllerDecorator.h
    include/genepool.h
    include/logger.h
    include/point.h
    include/Environment.h
    include/EnvironmentScene.h
    include/GameController.h
    include/Genotype.h
    include/Matrix.h
    include/cell.h
    tests/doctest.h
    libs/json/json.hpp
    include/frame.h
    include/mainwindow.h
    include/configs/Configuration.h
    include/configs/ConfigurationHandler.h
    include/configs/ConfigurationChain.h
    tests/test_Genotype.hpp
    tests/test_environment.hpp
)
set(FORMS
    ui/mainwindow.ui
)
set(RESOURCES
    resource.qrc
)

# invoke Qt moc, uic, and rcc
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
qt6_wrap_ui(UIS_HEADERS ${FORMS})
qt6_add_resources(QRC_SOURCES ${RESOURCES})

# tell CMake to include the output directory, where the ui_header_name.h file is generated
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add an executable using the sources
add_executable(Project_Ambient WIN32
    ${SOURCES}
    ${HEADERS}
    ${MOC_SOURCES}
    ${UIS_HEADERS}
    ${QRC_SOURCES}
)

# link against the Qt libraries
target_link_libraries(Project_Ambient PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# install the binary
install(TARGETS Project_Ambient DESTINATION bin)
