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
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtHello 
    main.cpp
    FinestraPrincipale.h)

# Collega le librerie di Qt al tuo eseguibile
target_link_libraries(QtHello PRIVATE Qt6::Widgets)