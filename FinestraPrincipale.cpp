#include "FinestraPrincipale.h"
#include "Worker.h"
#include <QProgressBar>
#include "MyThread.h"
#include "MyBtn.h"

// "private slots:" va messo solo quando si trova nel .h
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
    // QThread::sleep(5);

    /*
    Worker:
        - contiene codice da eseguire nel thread secondario
    Thread secondario (QThread):
        - permette l'esecuzione di tale codice non sul thread principale
        - QThread non esegue codice, gestisce l'esecuzione del codice presente
          su worker
    
    --> Cosi creo worker, lo muovo su quel thread, eseguo il codice,
    dico di cancellarlo al prossimo event loop, termino il thread e
    dico di cancellare anche lui al prossimo event loop

    --> Non importa l'ordine di scrittura dei connect, l'esecuzione
    non segue tale ordine; e' importante scriverli in ordine per 
    mantenere una struttura logica facile da leggere e comprendere
    */
    
    MyThread *thread = new MyThread(this);
    // todo: implementare distruttore per qthread
    Worker *worker = new Worker;

    connect(thread,&QThread::started,worker,&Worker::doWork);
    connect(worker, &Worker::progress, this, [this](int v){
        m_progressBar->setValue(v);
    });
    connect(worker,&Worker::finished,this,[this](){
        qDebug() << "Terminato";
    });

    /*
    Quando il worker finisce:
    - dice a se stesso di cancellarsi al prossimo event loop (worker - deleteLater)
    - dice al thread di terminare l'esecuzione di nuovi eventi (thread - quit)
    
    Quando riceve il comando quit, il thread termina tutte le diverse 
    operazioni (tra cui la cancellazione del worker)

    Cosi' facendo, la cancellazione del worker avviene prima
    della cancellazione del thread 

    Quando ha finito emette segnale finished, dicendo quindi
    di cancellarsi appena puo' al prossimo event loop
    */


    connect(worker,&Worker::finished,thread,&QThread::quit);
    // l'oggetto e' cancellato quando l'event loop termina, 
    // ovvero a thread terminato
    connect(thread,&QThread::finished,worker,&QObject::deleteLater);
    // 
    worker->moveToThread(thread);
    thread->start();
}

FinestraPrincipale::FinestraPrincipale(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Mac Shortcuts Dashboard");
    resize(500,250);
    
    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);

    MyBtn *btn1 = new MyBtn("Btn1", this);
    MyBtn *btn2 = new MyBtn("Btn2", this);
    MyBtn *btn3 = new MyBtn("Btn3", this);
    MyBtn *btn4 = new MyBtn("Close", this);
    MyBtn *btn5 = new MyBtn("Thread button",this);
    m_progressBar = new QProgressBar(this);
    m_progressBar->setValue(0);

    layoutPrincipale->addWidget(btn1);
    layoutPrincipale->addWidget(btn2);
    layoutPrincipale->addWidget(btn3);
    layoutPrincipale->addWidget(btn4);
    layoutPrincipale->addWidget(btn5);
    layoutPrincipale->addWidget(m_progressBar);

    // Signals e slots per 4 bottoni
    connect(btn1,&QPushButton::clicked,this,&FinestraPrincipale::slotA);
    connect(btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
        qDebug() << "Prova per stampare a terminale";
    });
    connect(btn3,&QPushButton::clicked,this,[this](){
        qDebug() << "Aumento contatore -> valore: " << ++counter;
        if(counter > my_project::N){
            alertLimiteCounter();
        }
    });
    connect(btn4,&QPushButton::clicked,this,&QWidget::close);
    connect(this,&FinestraPrincipale::alertLimiteCounter,this,&FinestraPrincipale::slotD);
    connect(btn5,&QPushButton::clicked,this,&FinestraPrincipale::slotE);
}

FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "Distruttore -> QWidget : FinestraPrincipale";
}
