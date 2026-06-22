#include "FinestraPrincipale.h"

#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QPointer>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

#include "ui_FinestraPrincipale.h"
#include "ui_DialogCounter.h"
#include "ui_DialogString.h"
#include "ui_DialogCheckbox.h"

#include "MyThread.h"
#include "Worker.h"

#include "MyBtn.h"
#include "MyDialog.h"

// Struttura file: impl - costruttore - distruttore - funzioni

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

        // Thread logics
        QPointer<MyThread> thread;
        QPointer<Worker> worker;

        QPointer<MyThread> counterThread1;
        QPointer<MyThread> counterThread2;
        QPointer<MyThread> counterThread3;

        QPointer<Worker> counterWorker1;
        QPointer<Worker> counterWorker2;
        QPointer<Worker> counterWorker3;

    private:
        int m_counter{0};
        int m_threadCounter1{0};
        int m_threadCounter2{0};
        int m_threadCounter3{0};
};

// Costruttore
FinestraPrincipale::FinestraPrincipale(QWidget *parent) : QMainWindow(parent), impl(std::make_unique<FinestraPrincipaleImpl>()) {

    m_ui = std::make_unique<Ui::MainWindow>();
    m_ui->setupUi(this);

    setWindowTitle("Qt Test Dashboard");
    // resize(800,300);

    auto btn2_lambda = [this]() {
        this->slotB();
        this->slotC();
    };

    auto btn3_lambda = [this](){
        impl->incrementCounter();
        this->m_ui->counterValueLabel->setText(QString::number(this->impl->getCounter()));
        qDebug() <<"Btn 3 -> Counter: " << impl->getCounter();
        if(impl->getCounter() > my_project::N){
            alertLimiteCounter();
        }
    };

    // 1. Connections
    connect(m_ui->btn1,&QPushButton::clicked,this,&FinestraPrincipale::slotA);
    connect(m_ui->btn2,&QPushButton::clicked,this,[this,btn2_lambda](){
        btn2_lambda();
    });
    connect(m_ui->btn3,&QPushButton::clicked,this,[this,btn3_lambda](){
        btn3_lambda();
    });
    connect(this,&FinestraPrincipale::alertLimiteCounter,this,&FinestraPrincipale::slotD);
    connect(m_ui->btn4,&QPushButton::clicked,this,&FinestraPrincipale::slotE);
    connect(m_ui->btn5,&QPushButton::clicked,this,&FinestraPrincipale::createDialogCounter);
    connect(m_ui->btn6,&QPushButton::clicked,this,&FinestraPrincipale::createDialogString);
    connect(m_ui->btn7,&QPushButton::clicked,this,&FinestraPrincipale::createDialogCheckbox);
    connect(m_ui->btn8,&QPushButton::clicked,this,&FinestraPrincipale::showPicture);

    connect(m_ui->closeBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(m_ui->actionQuit,&QAction::triggered,this,&QWidget::close);

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
        m_ui->m_progressBar->setValue(v);
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
        quando il worker finisce, il thread viene chiuso, 
        ma puo' ripartire con start
    */
    connect(impl->worker,&Worker::finished,impl->thread,&MyThread::quit);

    // Gestione 3 workers e 3 threads
    // il terzo thread parte al termine di uno dei due worker
    
    impl->counterThread1 = new MyThread();
    impl->counterThread2 = new MyThread();
    impl->counterThread3 = new MyThread();

    impl->counterWorker1 = new Worker();
    impl->counterWorker2 = new Worker();
    impl->counterWorker3 = new Worker();

    impl->counterWorker1->setObjectName("Thread 1");
    impl->counterWorker2->setObjectName("Thread 2");
    impl->counterWorker3->setObjectName("Thread 3");

    impl->counterWorker1->moveToThread(impl->counterThread1);
    impl->counterWorker2->moveToThread(impl->counterThread2);
    impl->counterWorker3->moveToThread(impl->counterThread3);

    connect(this->m_ui->btn9,&QPushButton::clicked,this,[this](){
        if((this->impl->counterThread1 && this->impl->counterThread1->isRunning()) ||
            (this->impl->counterThread2 && this->impl->counterThread2->isRunning())){
                qDebug() << "Threads gia' in esecuzione.";
            };
        this->impl->counterThread1->start();
        this->impl->counterThread2->start();
    });
    connect(impl->counterThread1,&QThread::started,impl->counterWorker1,[this](){
        this->impl->counterWorker1->evaluate(10);
    });

    connect(impl->counterThread2,&QThread::started,impl->counterWorker2,[this](){
        this->impl->counterWorker2->evaluate(20);
    });


    


} // costruttore

// Distruttore
FinestraPrincipale::~FinestraPrincipale() {
    qDebug() << "~ QWidget : FinestraPrincipale";
    emit cleanup();
}

// Slots
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

// Gestione chiusura finestra mentre worker e' in esecuzione
void FinestraPrincipale::closeEvent(QCloseEvent *event){
    if (impl->thread && impl->thread->isRunning()){
        qDebug() << "Thread not finished";
        QMessageBox::critical(this,"Error","Thread is running, please wait ...");
        event->ignore();
        return;
    }
    QMainWindow::closeEvent(event);
}

void FinestraPrincipale::createDialogCounter() {

    QDialog dialog (this);
    
    m_dialogCounter = std::make_unique<Ui::DCounter>();
    m_dialogCounter->setupUi(&dialog);

    // capture values -> sono variabili che la funzione sa gia' 
    // che verranno inclusi e utilizzati all'interno della funzione

    auto setCounterValue = [this,&dialog](int value){
        this->impl->setCounter(value);
        this->m_ui->counterValueLabel->setText(QString::number(this->impl->getCounter()));
        dialog.accept();
    };

    connect(m_dialogCounter->dialogConfirmBtn, &QDialogButtonBox::clicked, this, [setCounterValue,this](){
        setCounterValue(m_dialogCounter->spinBox->value());
    });

    qDebug() << "--- QDialog ---";
    dialog.exec(); // 
    qDebug() << "Uscita Finestra dialog";
}

void FinestraPrincipale::createDialogString(){
    
    QDialog dialog (this);
    
    m_dialogString = std::make_unique<Ui::DString>();
    m_dialogString->setupUi(&dialog);

    auto getComboBoxSelection = [this](QString text) {
        this->m_ui->labelString->setText(text);
    };

    QString choice = m_dialogString->comboBox->currentText();
    connect(m_dialogString->buttonBox,&QDialogButtonBox::clicked,this,[this,getComboBoxSelection](){
        getComboBoxSelection(this->m_dialogString->comboBox->currentText());
    });
    qDebug() << "--- QDialog ---";
    dialog.exec(); // 
    qDebug() << "Uscita Finestra dialog";
}

void FinestraPrincipale::createDialogCheckbox(){
    QDialog dialog(this);

    m_dialogCheckbox = std::make_unique<Ui::DCheckbox>();
    m_dialogCheckbox->setupUi(&dialog);

    auto getCheckboxInfo = [this] () {

        // Riempimento stringa inserita nella label
        this->m_ui->lineEditValueLabel->setText(this->m_dialogCheckbox->lineEdit->text());
    
        // Valutazione checkbox spuntate
        QString * checkboxesString = new QString();

        if(this->m_dialogCheckbox->checkBox_A->isChecked()){
            checkboxesString->append("- Opzione A -");
        }
        if(this->m_dialogCheckbox->checkBox_B->isChecked()){
            checkboxesString->append("- Opzione B -");
        }
        if(this->m_dialogCheckbox->checkBox_C->isChecked()){
            checkboxesString->append("- Opzione C -");
        }

        this->m_ui->checkboxesValueLabel->setText(* checkboxesString);

        // Valutazione radioButton scelto
        if(this->m_dialogCheckbox->radioButton_1->isChecked()){
            this->m_ui->radioButtonValueLabel->setText("Radio Button 1");
        }

        if(this->m_dialogCheckbox->radioButton_2->isChecked()){
            this->m_ui->radioButtonValueLabel->setText("Radio Button 2");

        }

    };

    connect(m_dialogCheckbox->buttonBox, &QDialogButtonBox::clicked, this, [this,getCheckboxInfo](){
        getCheckboxInfo();
    });

    qDebug() << "--- QDialog ---";
    dialog.exec(); // 
    qDebug() << "Uscita Finestra dialog";
}

void FinestraPrincipale::showPicture() {

    // Apro finestra per selezione file
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Scegli una immagine"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    QPointer <QLabel> pictureLabel = new QLabel();
    QPixmap pixmap(fileName);
    pixmap.scaled(100,100,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->m_ui->pictureLabelMainWindow->setPixmap(pixmap);

    pictureLabel->setPixmap(pixmap);
    pictureLabel->show();

}

