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

    dialogs/dialog_inheritance.h
    dialogs/dialog_inheritance.cpp
    dialogs/dialog_initial.h
    dialogs/dialog_initial.cpp
    dialogs/dialog_misc.h
    dialogs/dialog_misc.cpp
    dialogs/dialog_multithreading.h
    dialogs/dialog_multithreading.cpp
    dialogs/dialog_widgets.cpp
    dialogs/dialog_widgets.h

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

    ui/d_inheritance.ui
    ui/d_initial.ui
    ui/d_misc.ui
    ui/d_multithreading.ui
    ui/d_widgets.ui
    ui/MainWindow.ui

    )

# Collega le librerie di Qt all' eseguibile
target_link_libraries(QtProject1 PRIVATE Qt5::Widgets)

target_include_directories(QtProject1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})