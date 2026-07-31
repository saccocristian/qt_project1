#include "Triangle.h"
#include <QDebug>

Triangle::Triangle(double base, double height) : _base(base),
                                                 _height(height) 
{
    qDebug() << "Triangle::Triangle()";
    set_angles_number();
    set_sides_number();
}

Triangle::~Triangle(){
    qDebug() << "Triangle::~Triangle()";
}

void Triangle::set_angles_number(){
    m_angles_number = 3;
}

void Triangle::set_sides_number(){
    m_sides_number = 3;
}

double Triangle::get_area(){
    return get_base() * get_height();
}