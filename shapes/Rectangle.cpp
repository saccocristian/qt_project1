#include "Rectangle.h"
#include <QDebug>

Rectangle::Rectangle(double base, double height) : _base(base), 
                                                   _height(height)
    {

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

double Rectangle::get_area(){
    return _base * _height;
}
