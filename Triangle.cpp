#include "Triangle.h"
#include <QDebug>

Triangle::Triangle(){
    qDebug() << "Triangle::Triangle()";
    setNumeroAngoli();
    setNumeroLati();
}
Triangle::~Triangle(){
    qDebug() << "Triangle::~Triangle()";
}
void Triangle::setNumeroAngoli(){
    m_numeroAngoli = 3;
}

void Triangle::setNumeroLati(){
    m_numeroLati = 3;
}