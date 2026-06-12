#pragma once

#include <QObject>
#include <QPushButton>
#include <QDebug>


class MyBtn : public QPushButton {
    Q_OBJECT
    
    public:
    explicit MyBtn(const QString &text, QWidget *parent = nullptr) : QPushButton(text,parent) {}
    ~MyBtn();
};