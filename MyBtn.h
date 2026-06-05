#pragma once
#include <QObject>
#include <QPushButton>
#include <QDebug>


class MyBtn : public QPushButton {
    Q_OBJECT
    public:

    // questo mi permette di usare costruttore classe padre
    using QPushButton::QPushButton;
    ~MyBtn();
};