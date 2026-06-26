#include "Rectangle.h"
#include <QDebug>

Rectangle::Rectangle(){
    qDebug() << "Rectangle::Rectangle()";
    setNumeroAngoli();
    setNumeroLati();
}

Rectangle::~Rectangle(){
    qDebug() << "Rectangle::~Rectangle()";
}
void Rectangle::setNumeroAngoli(){
    m_numeroAngoli = 4;
}

void Rectangle::setNumeroLati(){
    m_numeroLati = 4;
}