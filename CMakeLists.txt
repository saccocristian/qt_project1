cmake_minimum_required(VERSION 3.16)
project(QtHello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Abilita il build system automatico di Qt per file di interfaccia, risorse e macro
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Cerca i pacchetti Qt (Homebrew viene rilevato automaticamente se hai impostato il PATH)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(QtProject1 
    main.cpp
    FinestraPrincipale.h
    FinestraPrincipale.cpp
    Worker.h
    Worker.cpp
    MyBtn.h
    MyBtn.cpp
    MyThread.h)

# Collega le librerie di Qt al tuo eseguibile
target_link_libraries(QtProject1 PRIVATE Qt5::Widgets)