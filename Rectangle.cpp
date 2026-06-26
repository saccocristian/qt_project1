#include "Rectangle.h"
#include <QDebug>

Rectangle::Rectangle(){
    qDebug() << "Rectangle::Rectangle()";
    set_angles_number();
    set_sides_number();
}

Rectangle::~Rectangle(){
    qDebug() << "Rectangle::~Rectangle()";
}

void Rectangle::set_angles_number(){
    m_angles_number = 4;
}

void Rectangle::set_sides_number(){
    m_sides_number = 4;
}