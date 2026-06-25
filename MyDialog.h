#pragma once

#include <QObject>
#include <QDialog>
#include <QDebug>

class MyDialog : public QDialog {
    Q_OBJECT

    public:
    using QDialog::QDialog;
    // explicit MyDialog(QWidget *parent = nullptr) : QDialog(parent) {}
    ~MyDialog();
};