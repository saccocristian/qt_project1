#include "FinestraPrincipale.h"

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
    QThread::sleep(5);
}

FinestraPrincipale::FinestraPrincipale(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Mac Shortcuts Dashboard");
    resize(500,250);

    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);

    QPushButton *btn1 = new QPushButton("Btn1", this);
    QPushButton *btn2 = new QPushButton("Btn2", this);
    QPushButton *btn3 = new QPushButton("Btn3", this);
    QPushButton *btn4 = new QPushButton("Close", this);
    QPushButton *btn5 = new QPushButton("Thread button",this);

    layoutPrincipale->addWidget(btn1);
    layoutPrincipale->addWidget(btn2);
    layoutPrincipale->addWidget(btn3);
    layoutPrincipale->addWidget(btn4);
    layoutPrincipale->addWidget(btn5);

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
