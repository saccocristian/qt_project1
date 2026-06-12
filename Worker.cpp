#include "Worker.h"
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent) {}

void Worker::doWork(){
    qDebug() << "Worker::doWork -- ThreadId:" << QThread::currentThreadId();
    for (int i=0; i<=100;++i){
        QThread::msleep(10);
        emit progress(i);
    }
    emit finished("Lavoro Finito");
}

Worker::~Worker(){
    qDebug() << "~ QObject : Worker";
}