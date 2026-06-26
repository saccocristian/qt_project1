#include "Shape.h"
#include <QDebug>

Shape::~Shape(){
    qDebug() << "Shape::~Shape()";
}

int Shape::get_angles_number() const {
    return m_angles_number;
}

int Shape::get_sides_number() const {
    return m_sides_number;
}