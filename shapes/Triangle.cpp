#include "Triangle.h"
#include <QDebug>

Triangle::Triangle(){
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