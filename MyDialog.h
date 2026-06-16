#pragma once

#include <QObject>
#include <QDialog>
#include <QDebug>

class MyDialog : public QDialog {
    Q_OBJECT

    public:
    explicit MyDialog(QWidget *parent = nullptr) : QDialog(parent) {}
    ~MyDialog();
};