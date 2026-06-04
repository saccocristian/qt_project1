#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>

namespace my_project {
    static constexpr int N = 20;
}
/*
Funzionamento base
---
4 pulsanti
- btn1 -> 1 slot A
- btn2 -> 1 slot B + 1 slot C
- btn3 -> 1 slot D
- btn4 -> 1 slot D
*/
class FinestraPrincipale : public QWidget {
    Q_OBJECT // per usare moc (meta-object compiler)

    signals:
        // A cosa serve questa sezione?
        void alertLimiteCounter();
        
    private slots:
        void slotA(){
            QMessageBox::information(this,"Msg1","Btn1 - Slot A");
        }
        void slotB(){
            QMessageBox::information(this,"Msg2","btn2 - Slot B");
        }
        void slotC(){
            QMessageBox::information(this,"Msg3","Btn2 - Slot C");
        }
        void slotD(){
            QMessageBox::warning(this,"Alert counter","Errore: counter raggiunto");
        }
    public:
    FinestraPrincipale(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Mac Shortcuts Dashboard");
        resize(500,250);
        
        QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
        
        QPushButton *btn1 = new QPushButton("Btn1", this);
        QPushButton *btn2 = new QPushButton("Btn2", this);
        QPushButton *btn3 = new QPushButton("Btn3", this);
        QPushButton *btn4 = new QPushButton("Close", this);

        layoutPrincipale->addWidget(btn1);
        layoutPrincipale->addWidget(btn2);
        layoutPrincipale->addWidget(btn3);
        layoutPrincipale->addWidget(btn4);
        
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
    }

    private:
        int counter = 0;

};