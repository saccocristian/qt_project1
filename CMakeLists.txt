cmake_minimum_required(VERSION 3.16)
project(QtHello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON) # per .ui file

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(QtProject1

    main.cpp
    MainWindow.h
    MainWindow.cpp

    dialogs/inheritance.h
    dialogs/inheritance.cpp
    dialogs/initial.h
    dialogs/initial.cpp
    dialogs/misc.h
    dialogs/misc.cpp
    dialogs/multithreading.h
    dialogs/multithreading.cpp
    dialogs/widgets.cpp
    dialogs/widgets.h
    dialogs/templates.h
    dialogs/templates.cpp
    
    inheritance/BaseClass.h
    inheritance/BaseClass.cpp
    inheritance/DerivedClass.h
    inheritance/DerivedClass.cpp

    qt_classes/MyBtn.h
    qt_classes/MyBtn.cpp
    qt_classes/MyDialog.h
    qt_classes/MyDialog.cpp

    shapes/Shape.cpp
    shapes/Rectangle.h
    shapes/Rectangle.cpp
    shapes/Triangle.h
    shapes/Triangle.cpp

    singleton/CalculatorSingleton.h
    singleton/CalculatorSingleton.cpp

    threading/Worker.h
    threading/Worker.cpp
    threading/MyThread.h

    shapes/Shape.h

    ui/inheritance.ui
    ui/initial.ui
    ui/misc.ui
    ui/multithreading.ui
    ui/widgets.ui
    ui/MainWindow.ui
    ui/templates.ui
    )

# Collega le librerie di Qt all' eseguibile
target_link_libraries(QtProject1 PRIVATE Qt5::Widgets)

target_include_directories(QtProject1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})