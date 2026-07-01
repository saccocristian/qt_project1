#include "MainWindow.h"

#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QPointer>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

#include "ui_MainWindow.h"
#include "ui_DialogCounter.h"
#include "ui_DialogString.h"
#include "ui_DialogCheckbox.h"

#include "MyThread.h"
#include "Worker.h"

#include "Rectangle.h"
#include "Triangle.h"

#include "MyBtn.h"
#include "MyDialog.h"

// Struttura file: impl - costruttore - distruttore - funzioni

class MainWindow::MainWindowImpl {

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
        QPixmap immagineOriginale;
        // Thread logics
        QPointer<MyThread> thread;
        QPointer<Worker> worker;

        QPointer<MyThread> counterThread1;
        QPointer<MyThread> counterThread2;
        QPointer<MyThread> counterThread3;

        QPointer<Worker> counterWorker1;
        QPointer<Worker> counterWorker2;
        QPointer<Worker> counterWorker3;

        std::unique_ptr<BaseClass> derivedClassObj;

        std::unique_ptr<Shape> shapeObj;
    private:
        int m_counter{0};
        int m_threadCounter1{0};
        int m_threadCounter2{0};
        int m_threadCounter3{0};
};

// Costruttore
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), impl(std::make_unique<MainWindowImpl>()) {

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
    // ptr to function
    void ( * ptrFunction)() = MainWindow::printFunctionExample;

    connect(m_ui->ptrFunctionBtn,&QPushButton::clicked,this,[this,ptrFunction](){
        ptrFunction();
    });

    CalculatorSingleton * calculator = CalculatorSingleton::getInstance();

    CalculatorSingleton * calculator_copy = CalculatorSingleton::getInstance();
    
    // 1. Connections
    connect(m_ui->btn1,&QPushButton::clicked,this,&MainWindow::slotA);
    connect(m_ui->btn2,&QPushButton::clicked,this,[this,btn2_lambda](){
        btn2_lambda();
    });
    connect(m_ui->btn3,&QPushButton::clicked,this,[this,btn3_lambda](){
        btn3_lambda();
    });
    connect(this,&MainWindow::alertLimiteCounter,this,&MainWindow::slotD);
    connect(m_ui->btn4,&QPushButton::clicked,this,&MainWindow::slotE);
    connect(m_ui->btn5,&QPushButton::clicked,this,&MainWindow::createDialogCounter);
    connect(m_ui->btn6,&QPushButton::clicked,this,&MainWindow::createDialogString);
    connect(m_ui->btn7,&QPushButton::clicked,this,&MainWindow::createDialogCheckbox);
    connect(m_ui->btn8,&QPushButton::clicked,this,&MainWindow::showPicture);

    impl->derivedClassObj = std::make_unique<DerivedClass>();

    connect(m_ui->btn10,&QPushButton::clicked,this,[this](){
        this->impl->derivedClassObj->stampaPopup();
    });
    connect(m_ui->btn11,&QPushButton::clicked,this,[this](){
        this->impl->derivedClassObj->stampaPopup(this->impl->getCounter());
    });
    
    connect(m_ui->btn12,&QPushButton::clicked,this,[this](){
        this->impl->derivedClassObj->stampaPopup("Hello World");
    });
    connect(m_ui->btn13,&QPushButton::clicked,this,[this](){
        this->impl->derivedClassObj->stampaPopupNonVirtual();
    });

    connect(m_ui->shapeOkBtn,&QPushButton::clicked,this,[this](){

        // Rectangle - Triangle
        // static_cast e dynamic_cast

        QString s = this->m_ui->shapeComboBox->currentText();
        if(s == "Rectangle"){
                this->impl->shapeObj = std::make_unique<Rectangle>();
        } else if (s == "Triangle") {
                this->impl->shapeObj = std::make_unique<Triangle>();
        }

        // dynamic_cast: uno dei due puntatori appena realizzati sara' nullptr perche' non sara' in grado di fare il cast
        Rectangle* rectangle_dynamic = dynamic_cast<Rectangle*>(this->impl->shapeObj.get());
        Triangle * triangle_dynamic = dynamic_cast<Triangle*>(this->impl->shapeObj.get());

        Rectangle * rectangle_static = static_cast<Rectangle*>(this->impl->shapeObj.get());
        Triangle * triangle_static = static_cast<Triangle*>(this->impl->shapeObj.get());

        // dynamic check behaviour: controlla effettivamente se la risorsa a cui punta coincida con lo stesso tipo; altrimenti da' un nullptr
        if (rectangle_dynamic != nullptr) {
            qDebug() << "rectDynamic e' un ptr valido a un oggetto Rectangle.";
        } else {
            qDebug() << "rectDynamic NON e' un ptr valido a un oggetto Rectangle.";
        }

        if (triangle_dynamic != nullptr) {
            qDebug() << "triangleDynamic e' un ptr valido a un oggetto Triangle.";
        } else {
            qDebug() << "triangleDynamic NON e' un ptr valido a un oggetto Triangle.";
        }

        // static check behaviour -> i puntatori non sono nulli in caso di errato assegnamento, ma se provassi a chiamare un metodo
        // che non appartiene alla classe a cui pensa di puntare da' errore!
        if (rectangle_static != nullptr) {
            qDebug() << "rectangleStatic e' un ptr valido a un oggetto Rectangle.";
        } else {
            qDebug() << "rectangleStatic NON e' un ptr valido a un oggetto Rectangle.";
        }

        if (triangle_static != nullptr) {
            qDebug() << "triangleStatic e' un ptr valido a un oggetto Triangle.";
        } else {
            qDebug() << "triangleStatic NON e' un ptr valido a un oggetto Triangle.";
        }

        qDebug() << "--- --- ---";
    });

    auto calculator_fn = [](CalculatorSingleton * calculator){
        calculator ->increaseCounter();
        calculator ->printCounter();
    };

    void (*ptr_calculator_fn)(CalculatorSingleton *) = calculator_fn;

    connect(m_ui->calcValueBtn,&QPushButton::clicked,this,[calculator,ptr_calculator_fn](){
        ptr_calculator_fn(calculator);
    });

    connect(m_ui->calcCopyValueBtn,&QPushButton::clicked,this,[calculator_copy,ptr_calculator_fn](){
        ptr_calculator_fn(calculator_copy);
    });

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
    connect(this,&MainWindow::cleanup,impl->thread,&MyThread::quit);
    connect(this,&MainWindow::cleanup,impl->thread,&MyThread::deleteLater);
    connect(this,&MainWindow::cleanup,impl->worker,&Worker::deleteLater);
    connect(this,&MainWindow::cleanup,this,[](){
        qDebug() << "------------------------------------";
        qDebug() << "MainWindow::cleanup -> thread::quit";
        qDebug() << "MainWindow::cleanup -> thread::deleteLater";
        qDebug() << "MainWindow::cleanup -> worker::deleteLater";
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

    // premo il btn, partono i 2 thread; 

    auto counterThreadStart = [this]() {
        if((impl->counterThread1 && impl->counterThread1->isRunning()) ||
            (impl->counterThread2 && impl->counterThread2->isRunning())){
                qDebug() << "Threads gia' in esecuzione.";
            }
        impl->counterThread1->start();
        impl->counterThread2->start();
    };

    connect(m_ui->btn9,&QPushButton::clicked,this,[this, counterThreadStart](){
        counterThreadStart();
    });

    connect(impl->counterThread1,&QThread::started,impl->counterWorker1,[this](){
        impl->counterWorker1->evaluate(5);
    });

    connect(impl->counterThread2,&QThread::started,impl->counterWorker2,[this](){
        impl->counterWorker2->evaluate(20);
    });

    auto checkCounterThread3 = [this](){
        if(impl->counterThread3->isRunning()){
            qDebug() <<"Counter Thread 3 gia' partito.";
            return;
        }
        impl->counterThread3->start();
    };
    
    connect(impl->counterWorker1,&Worker::finished,this,[this, checkCounterThread3](){
        checkCounterThread3();
    });

    connect(impl->counterWorker2,&Worker::finished,this,[this, checkCounterThread3](){
        checkCounterThread3();
    });
    connect(impl->counterWorker1,&Worker::finished,this,[](){
        qDebug() << "Thread Counter 1 finito";
    });
        connect(impl->counterWorker2,&Worker::finished,this,[](){
        qDebug() << "Thread Counter 2 finito";
    });

    connect(impl->counterThread3,&QThread::started,this,[this](){
        impl->counterWorker3->evaluate(5);
    });

    auto threadInit = [this](){
        if(!impl->counterWorker1->isFinished() || 
            !impl->counterWorker2->isFinished() ||
            !impl->counterWorker3->isFinished()){
                qDebug() << "Operazioni non terminate";
                emit retry();
                return;
            }
        impl->counterThread1->quit();
        impl->counterThread2->quit();
        impl->counterThread3->quit();
        qDebug() << "Threads inizializzati";
    };

    // Quando il counterThread3 finisce, faccio quit sui thread
    connect(impl->counterWorker3,&Worker::finished,this,[this, threadInit](){
        qDebug() << "Thread Counter 3 finito";
        threadInit();
    });

    connect(this,&MainWindow::retry,this, [this,threadInit](){
        threadInit();
    });

    connect(this,&MainWindow::cleanup,impl->counterThread1,&MyThread::quit);
    connect(this,&MainWindow::cleanup,impl->counterThread1,&MyThread::deleteLater);
    connect(this,&MainWindow::cleanup,impl->counterWorker1,&Worker::deleteLater);

    connect(this,&MainWindow::cleanup,impl->counterThread2,&MyThread::quit);
    connect(this,&MainWindow::cleanup,impl->counterThread2,&MyThread::deleteLater);
    connect(this,&MainWindow::cleanup,impl->counterWorker2,&Worker::deleteLater);

    connect(this,&MainWindow::cleanup,impl->counterThread3,&MyThread::quit);
    connect(this,&MainWindow::cleanup,impl->counterThread3,&MyThread::deleteLater);
    connect(this,&MainWindow::cleanup,impl->counterWorker3,&Worker::deleteLater);

} // costruttore

// Distruttore
MainWindow::~MainWindow() {
    qDebug() << "~ QWidget : MainWindow";
    emit cleanup();
}

// Slots
void MainWindow::slotA(){
    QMessageBox::information(this,"Msg1","Btn1 - Slot A");
}
void MainWindow::slotB(){
    QMessageBox::information(this,"Msg2","btn2 - Slot B");
}
void MainWindow::slotC(){
    QMessageBox::information(this,"Msg3","Btn2 - Slot C");
}
void MainWindow::slotD(){
    QMessageBox::warning(this,"Alert counter","Errore: counter raggiunto");
}
void MainWindow::slotE(){
    qDebug() << "------------------------------------";
    qDebug() << "Slot E -- ThreadId:" << QThread::currentThreadId();

    if(impl->thread && impl->thread->isRunning()){
        qDebug() << "Thread is already running.";
        return;
    }
    impl->thread->start();
}

// Gestione chiusura finestra mentre worker e' in esecuzione
void MainWindow::closeEvent(QCloseEvent *event){
    if (impl->thread && impl->thread->isRunning()){
        qDebug() << "Thread not finished";
        QMessageBox::critical(this,"Error","Thread is running, please wait ...");
        event->ignore();
        return;
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::createDialogCounter() {

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

void MainWindow::createDialogString(){
    
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

void MainWindow::createDialogCheckbox(){
    MyDialog dialog(this);

    m_dialogCheckbox = std::make_unique<Ui::DCheckbox>();
    m_dialogCheckbox->setupUi(&dialog);

    auto getCheckboxInfo = [this] () {

        // Riempimento stringa inserita nella label
        this->m_ui->lineEditValueLabel->setText(this->m_dialogCheckbox->lineEdit->text());
    
        // Valutazione checkbox spuntate
        QString * checkboxesString = new QString();

        if(m_dialogCheckbox->checkBox_A->isChecked()){
            checkboxesString->append("- Opzione A -");
        }
        if(m_dialogCheckbox->checkBox_B->isChecked()){
            checkboxesString->append("- Opzione B -");
        }
        if(m_dialogCheckbox->checkBox_C->isChecked()){
            checkboxesString->append("- Opzione C -");
        }

        m_ui->checkboxesValueLabel->setText(* checkboxesString);

        // Valutazione radioButton scelto
        if(m_dialogCheckbox->radioButton_1->isChecked()){
            m_ui->radioButtonValueLabel->setText("Radio Button 1");
        }

        if(m_dialogCheckbox->radioButton_2->isChecked()){
            m_ui->radioButtonValueLabel->setText("Radio Button 2");
        }

    };

    connect(m_dialogCheckbox->buttonBox, &QDialogButtonBox::clicked, this, [this,getCheckboxInfo](){
        getCheckboxInfo();
    });

    qDebug() << "--- QDialog ---";
    dialog.exec(); // 
    qDebug() << "Uscita Finestra dialog";
}

void MainWindow::showPicture() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Scegli una immagine"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty()) {
        return; // L'utente ha annullato la selezione
    }

    // Salva la pixmap originale nell'impl
    impl->immagineOriginale = QPixmap(fileName);

    // Diamo il permesso alla label di espandere/restringere il suo contenuto visivo
    m_ui->pictureLabelMainWindow->setScaledContents(true);

    // Forziamo un primo ridimensionamento basato sulla larghezza attuale
    if (!impl->immagineOriginale.isNull()) {
        int larghezzaFinestra = this->width();
        
        // Scaliamo mantenendo le proporzioni
        QPixmap scalata = impl->immagineOriginale.scaledToWidth(larghezzaFinestra, Qt::SmoothTransformation);
        m_ui->pictureLabelMainWindow->setPixmap(scalata);
    }
}

void MainWindow::printFunctionExample(){
    qDebug() << "Usage of ptr to function";
}
