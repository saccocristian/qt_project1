#include "dialog_multithreading.h"
#include "ui_d_multithreading.h"

#include "threading/MyThread.h"
#include "threading/Worker.h"

#include <QPointer>
#include <QMessageBox>

class dialog_multithreading::dialog_multithreading_impl{
    public:
        QPointer<MyThread> thread;
        QPointer<Worker> worker;

        QPointer<MyThread> counterThread1;
        QPointer<MyThread> counterThread2;
        QPointer<MyThread> counterThread3;

        QPointer<Worker> counterWorker1;
        QPointer<Worker> counterWorker2;
        QPointer<Worker> counterWorker3;
    private:
};

dialog_multithreading::dialog_multithreading(QWidget * parent) : QDialog(parent), m_impl(std::make_unique<dialog_multithreading_impl>()) {
    m_ui = std::make_unique<Ui::d_multithreading>();
    m_ui->setupUi(this);

    m_impl->thread = new MyThread();
    m_impl->worker = new Worker();
    m_impl->worker->moveToThread(m_impl->thread);

    connect(m_ui->btn1,&QPushButton::clicked,this,&dialog_multithreading::startThread);
    connect(m_impl->thread,&QThread::started,m_impl->worker,&Worker::doWork);
    connect(m_impl->thread,&QThread::started,this,[](){
        qDebug() << "thread::started\t->\tworker::doWork -- ThreadId:" << QThread::currentThreadId();
    });
    connect(m_impl->worker, &Worker::progress, this, [this](int v){
        if(v==0){
            qDebug() << "ProgressBar -- ThreadId: " <<QThread::currentThreadId();
        }
        m_ui->m_progressBar->setValue(v);
    });

}

dialog_multithreading::~dialog_multithreading(){
    
}

void dialog_multithreading::startThread(){
    qDebug() << "------------------------------------";
    qDebug() << "dialog_multithreading::startThread -- ThreadId:" << QThread::currentThreadId();

    if(m_impl->thread && m_impl->thread->isRunning()){
        qDebug() << "Thread is already running.";
        return;
    }
    m_impl->thread->start();
}

void dialog_multithreading::closeEvent(QCloseEvent *event){
    if (m_impl->thread && m_impl->thread->isRunning()){
        qDebug() << "Thread not finished";
        QMessageBox::critical(this,"Error","Thread is running, please wait ...");
        event->ignore();
        return;
    }
    dialog_multithreading::closeEvent(event);
}