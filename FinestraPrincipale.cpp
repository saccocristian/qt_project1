
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
    btn1 = new MyBtn("Btn1: 1 Signal 1 Slot",this);
    btn2 = new MyBtn("Btn2: 1 Signal 2 Slot",this);
    btn3 = new MyBtn("Btn3: Incremento Counter",this);
    btn4 = new MyBtn("Btn4: Chiusura App",this);
    btn5 = new MyBtn("Btn5: Simulazione Multithreading",this);

    btn1->setObjectName("btn1");
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

    thread = new MyThread();
    thread->setObjectName("MyThreadName");

    worker = new Worker();
    worker->moveToThread(thread);

    //
    connect(thread,&QThread::started,worker,&Worker::doWork);
    connect(thread,&QThread::started,this,[](){
        qDebug() << "thread::started\t->\tworker::doWork -- ThreadId:" << QThread::currentThreadId();
    });

    //
    connect(worker, &Worker::progress, this, [this](int v){
        qDebug() << "ProgressBar -- ThreadId: " <<QThread::currentThreadId();
        m_progressBar->setValue(v);
    });

    //
    connect(this,&FinestraPrincipale::cleanup,thread,&MyThread::quit);
    connect(this,&FinestraPrincipale::cleanup,this,[](){
        qDebug() << "FinestraPrincipale::cleanup\t->\tthread::quit";
    });

    connect(this,&FinestraPrincipale::cleanup,thread,&MyThread::deleteLater);

    connect(this,&FinestraPrincipale::cleanup,worker,&Worker::deleteLater);
    connect(this,&FinestraPrincipale::cleanup,this,[](){
        qDebug() << "";
    });

    connect(worker,&Worker::finished,thread,&MyThread::quit);
}

// Distruttore
FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "Distruttore -> QWidget : FinestraPrincipale";
    // TODO: gestire chiusura finestra con doWork ancora in esecuzione
    emit cleanup();
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
    
    qDebug() << "Slot E -- ThreadId:" << QThread::currentThreadId();

    if(thread && thread->isRunning()){
        qDebug() << "Thread is already running.";
        return;
    }

    
    thread->start();
}
