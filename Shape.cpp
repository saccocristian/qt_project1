#include "Shape.h"
#include <QDebug>

Shape::~Shape(){
    qDebug() << "Shape::~Shape()";
}

int Shape::getNumeroAngoli(){
    return m_numeroAngoli;
}

int Shape::getNumeroLati(){
    return m_numeroLati;
}