#include "FinestraPrincipale.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QPointer>
#include <QLabel>
#include <QSpinBox>

#include <memory.h>

#include "MyBtn.h"
#include "MyThread.h"
#include "Worker.h"
#include "MyDialog.h"
/* Struttura:
 costruttore - distruttore - funzioni
*/

class FinestraPrincipale::FinestraPrincipaleImpl {

    public:

        int getCounter() const {
            return m_counter;
        }

        void setCounter(const int counter){
            m_counter = counter;
        }

        void incrementCounter(){
            m_counter +=1;
        }
        QPointer<QVBoxLayout> layoutPrincipale;
        QPointer <QWidget> widget;
        QPointer<MyBtn> btn1;
        QPointer<MyBtn> btn2;
        QPointer<MyBtn> btn3;
        QPointer<MyBtn> btn4;
        QPointer<MyBtn> btn5;
        QPointer<MyBtn> btn6;
        QPointer<QProgressBar> m_progressBar;

        // Thread logics
        QPointer<MyThread> thread;
        QPointer<Worker> worker;

    private:
        int m_counter{0};
};

// Costruttore
FinestraPrincipale::FinestraPrincipale(QMainWindow *parent) : QMainWindow(parent),impl(new FinestraPrincipaleImpl) {
    /*  Sezione GUI - Struttura Main window:
        - https://doc.qt.io/qt-6/qtwidgets-mainwindows-menus-example.html
        - MainWindow -> CentralWidget -> QVBoxLayout -> btns + progress bar
    */
    setWindowTitle("Qt Test Dashboard");
    resize(800,300);

    // Inizializzazione impl messa dove c'e' il costruttore
    // impl = new FinestraPrincipaleImpl();

    impl->widget = new QWidget();
    setCentralWidget(impl->widget);

    impl->layoutPrincipale = new QVBoxLayout();

    impl->btn1 = new MyBtn("Btn1: 1 Signal 1 Slot",this);
    impl->btn2 = new MyBtn("Btn2: 1 Signal 2 Slot",this);
    impl->btn3 = new MyBtn("Btn3: Incremento Counter",this);
    impl->btn4 = new MyBtn("Btn4: Chiusura App",this);
    impl->btn5 = new MyBtn("Btn5: Simulazione Multithreading",this);
    impl->btn6 = new MyBtn("Btn6: Apertura QDialog",this);

    impl->btn1->setObjectName("btn1");
    impl->btn2->setObjectName("btn2");
    impl->btn3->setObjectName("btn3");
    impl->btn4->setObjectName("btn4");
    impl->btn5->setObjectName("btn5");
    impl->btn6->setObjectName("btn6");

    impl->m_progressBar = new QProgressBar (this);
    impl->m_progressBar->setValue(0);

    impl->layoutPrincipale->addWidget(impl->btn1);
    impl->layoutPrincipale->addWidget(impl->btn2);
    impl->layoutPrincipale->addWidget(impl->btn3);
    impl->layoutPrincipale->addWidget(impl->btn4);
    impl->layoutPrincipale->addWidget(impl->btn5);
    impl->layoutPrincipale->addWidget(impl->btn6);
    impl->layoutPrincipale->addWidget(impl->m_progressBar);

    impl->widget ->setLayout(impl->layoutPrincipale);

    // Sezione Signals e slots buttons
    connect(impl->btn1,&QPushButton::clicked,this,&FinestraPrincipale::slotA);
    connect(impl->btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
    });
    connect(impl->btn3,&QPushButton::clicked,this,[this](){
        impl->incrementCounter();
        qDebug() <<"Btn 3 -> Counter: " << impl->getCounter();
        if(impl->getCounter() > my_project::N){
            alertLimiteCounter();
        }
    });
    connect(this,&FinestraPrincipale::alertLimiteCounter,this,&FinestraPrincipale::slotD);
    connect(impl->btn4,&QPushButton::clicked,this,&QWidget::close);
    connect(impl->btn5,&QPushButton::clicked,this,&FinestraPrincipale::slotE);
    connect(impl->btn6,&MyBtn::clicked,this,&FinestraPrincipale::createDialog);

    // Sezione Thread
    impl->thread = new MyThread();
    impl->thread->setObjectName("MyThreadName");

    impl->worker = new Worker();
    impl->worker->moveToThread(impl->thread);

    // Gestione esecuzione worker::doWork
    connect(impl->thread,&QThread::started,impl->worker,&Worker::doWork);
    connect(impl->thread,&QThread::started,this,[](){
        qDebug() << "thread::started\t->\tworker::doWork -- ThreadId:" << QThread::currentThreadId();
    });
    connect(impl->worker, &Worker::progress, this, [this](int v){
        if(v==0){
            qDebug() << "ProgressBar -- ThreadId: " <<QThread::currentThreadId();
        }
        impl->m_progressBar->setValue(v);
    });

    /* Gestione chiusura finestra:
        - Quando invoco distruttore finestra, emetto cleanup()
        - cleanup si occupa di gestire cancellazione thread e worker
    */
    connect(this,&FinestraPrincipale::cleanup,impl->thread,&MyThread::quit);
    connect(this,&FinestraPrincipale::cleanup,impl->thread,&MyThread::deleteLater);
    connect(this,&FinestraPrincipale::cleanup,impl->worker,&Worker::deleteLater);
    connect(this,&FinestraPrincipale::cleanup,this,[](){
        qDebug() << "------------------------------------";
        qDebug() << "FinestraPrincipale::cleanup -> thread::quit";
        qDebug() << "FinestraPrincipale::cleanup -> thread::deleteLater";
        qDebug() << "FinestraPrincipale::cleanup -> worker::deleteLater";
    });

    /* Gestione chiusura thread per riutilizzo:
        - quando il worker finisce, il thread viene 
            chiuso, ma puo' ripartire con start
    */
    connect(impl->worker,&Worker::finished,impl->thread,&MyThread::quit);
}

// Distruttore
FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "~ QWidget : FinestraPrincipale";
    delete impl;
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
    qDebug() << "------------------------------------";
    qDebug() << "Slot E -- ThreadId:" << QThread::currentThreadId();

    if(impl->thread && impl->thread->isRunning()){
        qDebug() << "Thread is already running.";
        return;
    }
    impl->thread->start();
}

void FinestraPrincipale::closeEvent(QCloseEvent *event){
    if (impl->thread && impl->thread->isRunning()){
        qDebug() << "Thread not finished";
        QMessageBox::critical(this,"Error","Thread is running, please wait ...");
        event->ignore();
        return;
    }
    QMainWindow::closeEvent(event);
}

void FinestraPrincipale::createDialog() {
     // Finestra dialog secondaria:
    // finestra -> layout -> label + spinbox + btn conferma + 

    MyDialog finestraDialog(this);

    finestraDialog.setWindowTitle("Counter Dialog");
    finestraDialog.resize(500,100);

    QVBoxLayout * layoutDialog = new QVBoxLayout(&finestraDialog);
    QLabel * labelDialog = new QLabel("Inserire valore counter",&finestraDialog);
    QSpinBox * spinboxDialog = new QSpinBox(&finestraDialog);
    spinboxDialog->setRange(0,100);
    
    MyBtn * resetCounterBtn = new MyBtn("Reset Counter",&finestraDialog);
    MyBtn * setCounterBtn = new MyBtn("Confirm",&finestraDialog);

    layoutDialog->addWidget(labelDialog);
    layoutDialog->addWidget(spinboxDialog);
    layoutDialog->addWidget(resetCounterBtn);
    layoutDialog->addWidget(setCounterBtn);
    finestraDialog.setLayout(layoutDialog);

    auto setCounterValue = [this, &spinboxDialog, &finestraDialog](int value){
        switch(value) {
        case 1:
            this->impl->setCounter(spinboxDialog->value());
            finestraDialog.close();
            break;
        case 0:
            this->impl->setCounter(0);
            QMessageBox::information(this,"Reset Counter","Variabile impostata a zero");
            finestraDialog.close();
            break;
        }
    };
    connect(setCounterBtn,&MyBtn::clicked,this, [&setCounterValue](){
        setCounterValue(1);
    });
    connect(resetCounterBtn,&MyBtn::clicked,this,[&setCounterValue](){
        setCounterValue(0);
    });
    qDebug() << "--- QDialog ---";
    finestraDialog.exec(); // 
    qDebug() << "Uscita Finestra dialog";
}