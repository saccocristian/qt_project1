
#include "FinestraPrincipale.h"

/*
Struttura:
- costruttore
- distruttore
- funzioni
*/


// Costruttore
FinestraPrincipale::FinestraPrincipale(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Qt Test Dashboard");
    resize(500,250);

    layoutPrincipale = new QVBoxLayout(this);
    
    // make_unique -> QPointer
    btn1 = new MyBtn("Btn1 - 1 signal 1 slot",this);
    btn2 = new MyBtn("Btn2 - 1 signal 2 slot",this);
    btn3 = new MyBtn("Btn3 - incremento counter",this);
    btn4 = new MyBtn("Btn4 - chiusura app",this);
    btn5 = new MyBtn("Btn5 - simulazione multithreading",this);

    btn1->setObjectName("Btn1");
    btn2->setObjectName("btn2");
    btn3->setObjectName("btn3");
    btn4->setObjectName("btn4");
    btn5->setObjectName("btn5");

    m_progressBar = new QProgressBar (nullptr);
    m_progressBar->setValue(0);

    layoutPrincipale->addWidget(btn1);
    layoutPrincipale->addWidget(btn2);
    layoutPrincipale->addWidget(btn3);
    layoutPrincipale->addWidget(btn4);
    layoutPrincipale->addWidget(btn5);
    layoutPrincipale->addWidget(m_progressBar);
    
    qDebug() << "----- Prova -----";

    // Signals e slots per 4 bottoni
    connect(btn1,&QPushButton::clicked,this,[this](){
        slotA();
        qDebug() << "Slot A";
    });
    connect(btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
        qDebug() << "Slot B";
    });
    connect(btn3,&QPushButton::clicked,this,[this](){
        qDebug() <<"Aumento contatore -> valore: " << ++counter;
        if(counter > my_project::N){
            alertLimiteCounter();
        }
        qDebug() << "Slot C";
    });
    connect(this,&FinestraPrincipale::alertLimiteCounter,this,&FinestraPrincipale::slotD);

    connect(btn4,&QPushButton::clicked,this,&QWidget::close);
    connect(btn5,&QPushButton::clicked,this,&FinestraPrincipale::slotE);
    qDebug() << "----- Prova2 -----";
}

// Distruttore

FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "Distruttore -> QWidget : FinestraPrincipale";
}

//Funzioni

void FinestraPrincipale::slotA(){
    QMessageBox::information(this,"Msg1","Btn1 - Slot A");
}
void FinestraPrincipale::slotB(){
    QMessageBox::information(this,"Msg2","btn2 - Slot B");
}
void FinestraPrincipale::slotC(){
    QMessageBox::information(this,"Msg3","Btn2 - Slot C");
}
void FinestraPrincipale::slotD(){
    QMessageBox::warning(this,"Alert counter","Errore: counter raggiunto");
}
void FinestraPrincipale::slotE(){
    
    qDebug() << "Slot E";

    thread = new MyThread();
    thread->setObjectName("MyThreadName");

    worker = new Worker();
    worker->moveToThread(thread);

    /*
    1. thread::started    -> worker::doWork
    2. worker::finished   -> thread::quit
    3. worker::finished   -> worker::deleteLater
    4. thread::finished   -> thread::deleteLater
    */

    // 1.
    connect(thread,&QThread::started,worker,&Worker::doWork);
    connect(thread,&QThread::started,this,[](){
        qDebug() << "1. thread::started\t\t->\tworker::doWork";
    });

    // 1a.
    connect(worker, &Worker::progress, this, [this](int v){
        m_progressBar->setValue(v);
    });

    // 2.
    connect(worker,&Worker::finished,thread,&MyThread::quit);
    connect(worker,&Worker::finished,this,[](){
        qDebug() << "2. worker::finished\t\t->\tthread::quit";
    });

    // 3.
    connect(worker,&Worker::finished,worker,&Worker::deleteLater);
    connect(thread,&MyThread::finished,this,[](){
        qDebug() << "3. worker::finished\t\t->\tworker::deleteLater";
    });

    // 4. 
    connect(thread,&MyThread::finished,thread,&MyThread::deleteLater);
    connect(thread,&MyThread::finished,this,[](){
        qDebug() << "4. thread::finished\t\t->\tthread::deleteLater";
    });
    
    thread->start();
}
