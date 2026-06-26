#pragma once

class Shape {

    protected:
        int m_numeroAngoli;
        int m_numeroLati;

    public:
    virtual ~Shape();

    virtual void setNumeroAngoli() = 0;
    int getNumeroAngoli();

    virtual void setNumeroLati() = 0;
    int getNumeroLati();

};