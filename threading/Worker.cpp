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

// sleepTime -> in ms
void Worker::evaluate(int sleepTime){
    if(m_isStarted) {
        qDebug() << "Worker gia' in esecuzione";
        return;
    }
    m_isStarted = true;
    qDebug() << this->objectName() + " -- ThreadId: " << QThread::currentThreadId();

    for(int i=0; i<=10;i+=1){
        qDebug() << this->objectName() +  " -> Value: " << i;
        QThread::msleep(sleepTime);
    }
    m_isStarted = false;
    m_isFinished = true;
    emit finished(this->objectName() + " -> Finished");
}

bool Worker::isFinished(){
    return m_isFinished;
}