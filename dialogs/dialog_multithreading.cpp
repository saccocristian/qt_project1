#include "dialog_multithreading.h"
#include "../ui/ui_d_multithreading.h"

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
    // connect(m_impl->thread,&QThread::started,m_impl->worker,&Worker::doWork);
    connect(m_impl->thread,&QThread::started,this,[this](){
        m_impl->worker->doWork();
        qDebug() << "thread::started\t->\tworker::doWork -- ThreadId:" << QThread::currentThreadId();
    });
    connect(m_impl->worker, &Worker::progress, this, [this](int v){
        if(v==0){
            qDebug() << "ProgressBar -- ThreadId: " <<QThread::currentThreadId();
        }
        m_ui->m_progressBar->setValue(v);
    });
    
    connect(m_impl->worker,&Worker::finished,m_impl->thread,&MyThread::quit);


    connect(this,&dialog_multithreading::cleanup,m_impl->thread,&MyThread::quit);
    connect(this,&dialog_multithreading::cleanup,m_impl->thread,&MyThread::deleteLater);
    connect(this,&dialog_multithreading::cleanup,m_impl->worker,&Worker::deleteLater);
    connect(this,&dialog_multithreading::cleanup,this,[](){
        qDebug() << "------------------------------------";
        qDebug() << "dialog_multithreading::cleanup -> thread::quit";
        qDebug() << "dialog_multithreading::cleanup -> thread::deleteLater";
        qDebug() << "dialog_multithreading::cleanup -> worker::deleteLater";
    });
    m_impl->counterThread1 = new MyThread();
    m_impl->counterThread2 = new MyThread();
    m_impl->counterThread3 = new MyThread();

    m_impl->counterWorker1 = new Worker();
    m_impl->counterWorker2 = new Worker();
    m_impl->counterWorker3 = new Worker();

    m_impl->counterWorker1->setObjectName("Thread 1");
    m_impl->counterWorker2->setObjectName("Thread 2");
    m_impl->counterWorker3->setObjectName("Thread 3");

    m_impl->counterWorker1->moveToThread(m_impl->counterThread1);
    m_impl->counterWorker2->moveToThread(m_impl->counterThread2);
    m_impl->counterWorker3->moveToThread(m_impl->counterThread3);

    // premo il btn, partono i 2 thread; 

    auto counterThreadStart = [this]() {
        if((m_impl->counterThread1 && m_impl->counterThread1->isRunning()) ||
            (m_impl->counterThread2 && m_impl->counterThread2->isRunning())){
                qDebug() << "Threads gia' in esecuzione.";
            }
        m_impl->counterThread1->start();
        m_impl->counterThread2->start();
    };

    connect(m_ui->btn2,&QPushButton::clicked,this,[this, counterThreadStart](){
        counterThreadStart();
    });

    // quando partono i due thread eseguo evaluate per entrambi, i quali emettono segnale finished() alla fine
    connect(m_impl->counterThread1,&QThread::started,m_impl->counterWorker1,[this](){
        m_impl->counterWorker1->evaluate(1000);
    });

    connect(m_impl->counterThread2,&QThread::started,m_impl->counterWorker2,[this](){
        m_impl->counterWorker2->evaluate(2000);
    });

    // non appena uno dei due finisce, viene lanciato checkCounterThread3 per far partire il terzo thread
    auto checkCounterThread3 = [this](){
        if(m_impl->counterThread3->isRunning()){
            qDebug() <<"Counter Thread 3 gia' partito.";
            return;
        }
        m_impl->counterThread3->start();
    };
    
    connect(m_impl->counterWorker1,&Worker::finished,this,[this, checkCounterThread3](){
        checkCounterThread3();
    });

    connect(m_impl->counterWorker2,&Worker::finished,this,[this, checkCounterThread3](){
        checkCounterThread3();
    });

    connect(m_impl->counterWorker1,&Worker::finished,this,[](){
        qDebug() << "Thread Counter 1 finito";
    });
        connect(m_impl->counterWorker2,&Worker::finished,this,[](){
        qDebug() << "Thread Counter 2 finito";
    });


    connect(m_impl->counterThread3,&QThread::started,this,[this](){
        m_impl->counterWorker3->evaluate(2000);
    });

    auto threadInit = [this](){
        if(!m_impl->counterWorker1->isFinished() || 
           !m_impl->counterWorker2->isFinished() ||
           !m_impl->counterWorker3->isFinished()){
                qDebug() << "Operazioni non terminate";
                emit retry();
                return;
            }
        m_impl->counterThread1->quit();
        m_impl->counterThread2->quit();
        m_impl->counterThread3->quit();
        qDebug() << "Threads inizializzati";
    };

    // Quando il counterThread3 finisce, faccio quit sui thread
    connect(m_impl->counterWorker3,&Worker::finished,this,[this, threadInit](){
        qDebug() << "Thread Counter 3 finito";
        threadInit();
    });

    connect(this,&dialog_multithreading::retry,this, [this,threadInit](){
        threadInit();
    });

    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread1,&MyThread::quit);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread1,&MyThread::deleteLater);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterWorker1,&Worker::deleteLater);

    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread2,&MyThread::quit);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread2,&MyThread::deleteLater);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterWorker2,&Worker::deleteLater);

    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread3,&MyThread::quit);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterThread3,&MyThread::deleteLater);
    connect(this,&dialog_multithreading::cleanup,m_impl->counterWorker3,&Worker::deleteLater);
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