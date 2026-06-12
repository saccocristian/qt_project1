#pragma once
#include <QObject>
#include <QDebug>
#include <QThread>

class MyThread : public QThread {
    Q_OBJECT
    public:
        MyThread(QObject * parent = nullptr) : QThread(parent){
        }

        ~MyThread(){
            qDebug() << "Distruttore MyThread";
        }
};