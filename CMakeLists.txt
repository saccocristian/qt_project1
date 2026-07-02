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

    threading/Worker.h
    threading/Worker.cpp
    threading/MyThread.h

    qt_classes/MyBtn.h
    qt_classes/MyBtn.cpp
    qt_classes/MyDialog.h
    qt_classes/MyDialog.cpp

    inheritance/BaseClass.h
    inheritance/BaseClass.cpp
    inheritance/DerivedClass.h
    inheritance/DerivedClass.cpp

    shapes/Shape.h
    shapes/Shape.cpp
    shapes/Rectangle.h
    shapes/Rectangle.cpp
    shapes/Triangle.h
    shapes/Triangle.cpp

    singleton/Calculator.h
    singleton/Calculator.cpp
    
    ui/MainWindow.ui
    ui/DialogCounter.ui
    ui/DialogString.ui
    ui/DialogCheckbox.ui)

# Collega le librerie di Qt all' eseguibile
target_link_libraries(QtProject1 PRIVATE Qt5::Widgets)