#include "FinestraPrincipale.h"

/*
Struttura:
- costruttore
- distruttore
- funzioni
*/

// Costruttore
FinestraPrincipale::FinestraPrincipale(QMainWindow *parent) : QMainWindow(parent) {
    setWindowTitle("Qt Test Dashboard");
    resize(800,300);

    // Sezione GUI
    /*  Struttura Main window:
        - https://doc.qt.io/qt-6/qtwidgets-mainwindows-menus-example.html
        - MainWindow -> CentralWidget -> QVBoxLayout -> btns + progress bar
    */

    QPointer <QWidget> widget = new QWidget();
    setCentralWidget(widget);

    layoutPrincipale = new QVBoxLayout(this);

    btn1 = new MyBtn("Btn1: 1 Signal 1 Slot",this);
    btn2 = new MyBtn("Btn2: 1 Signal 2 Slot",this);
    btn3 = new MyBtn("Btn3: Incremento Counter",this);
    btn4 = new MyBtn("Btn4: Chiusura App",this);
    btn5 = new MyBtn("Btn5: Simulazione Multithreading",this);
    btn6 = new MyBtn("Btn6: Apertura QDialog");

    btn1->setObjectName("btn1");
    btn2->setObjectName("btn2");
    btn3->setObjectName("btn3");
    btn4->setObjectName("btn4");
    btn5->setObjectName("btn5");
    btn6->setObjectName("btn6");

    m_progressBar = new QProgressBar (nullptr);
    m_progressBar->setValue(0);

    layoutPrincipale->addWidget(btn1);
    layoutPrincipale->addWidget(btn2);
    layoutPrincipale->addWidget(btn3);
    layoutPrincipale->addWidget(btn4);
    layoutPrincipale->addWidget(btn5);
    layoutPrincipale->addWidget(btn6);
    layoutPrincipale->addWidget(m_progressBar);

    widget ->setLayout(layoutPrincipale);
    
    // Finestra dialog secondaria
    finestraDialog = new QDialog(this);
    finestraDialog->setWindowTitle("Counter Dialog");
    finestraDialog->resize(500,400);
    
    labelDialogSecondario = new QLabel(finestraDialog);
    labelDialogSecondario->setText("Inserire valore counter");

    // Sezione Signals e slots buttons
    connect(btn1,&QPushButton::clicked,this,&FinestraPrincipale::slotA);
    connect(btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
    });
    connect(btn3,&QPushButton::clicked,this,[this](){
        qDebug() <<"Btn 3 -> Counter: " << ++counter;
        if(counter > my_project::N){
            alertLimiteCounter();
        }
    });
    connect(this,&FinestraPrincipale::alertLimiteCounter,this,&FinestraPrincipale::slotD);
    connect(btn4,&QPushButton::clicked,this,&QWidget::close);
    connect(btn5,&QPushButton::clicked,this,&FinestraPrincipale::slotE);
    connect(btn6,&MyBtn::clicked,finestraDialog,&QDialog::exec);

    // Sezione Thread
    thread = new MyThread();
    thread->setObjectName("MyThreadName");

    worker = new Worker();
    worker->moveToThread(thread);

    // Gestione esecuzione worker::doWork
    connect(thread,&QThread::started,worker,&Worker::doWork);
    connect(thread,&QThread::started,this,[](){
        qDebug() << "thread::started\t->\tworker::doWork -- ThreadId:" << QThread::currentThreadId();
    });

    connect(worker, &Worker::progress, this, [this](int v){
        if(v==0){
            qDebug() << "ProgressBar -- ThreadId: " <<QThread::currentThreadId();
        }
        m_progressBar->setValue(v);
    });

    /* Gestione chiusura finestra:
        - Quando invoco distruttore finestra, emetto cleanup()
        - cleanup si occupa di gestire cancellazione thread e worker
    */
    connect(this,&FinestraPrincipale::cleanup,thread,&MyThread::quit);
    connect(this,&FinestraPrincipale::cleanup,thread,&MyThread::deleteLater);
    connect(this,&FinestraPrincipale::cleanup,worker,&Worker::deleteLater);

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
    connect(worker,&Worker::finished,thread,&MyThread::quit);

    /* Gestione chiusura thread quando chiudo finestra prima che finisca doWork

    */
}

// Distruttore
FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "~ QWidget : FinestraPrincipale";
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
    qDebug() << "------------------------------------";
    qDebug() << "Slot E -- ThreadId:" << QThread::currentThreadId();

    if(thread && thread->isRunning()){
        qDebug() << "Thread is already running.";
        return;
    }

    thread->start();
}

void FinestraPrincipale::closeEvent(QCloseEvent *event){
    if (thread && thread->isRunning()){
        qDebug() << "Thread not finished";
        QMessageBox::critical(this,"Error","Thread is running, please wait ...");

        event->ignore();
        return;
    }
    QMainWindow::closeEvent(event);
}