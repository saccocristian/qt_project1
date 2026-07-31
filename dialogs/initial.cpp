#include "initial.h"
#include "../ui/ui_initial.h"

#include <QMessageBox>
#include <QDebug>

namespace constant{
    int N = 20;
}
class initial::initial_impl{

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

    private:
        int m_counter{0};
};

initial::initial(QWidget * parent) : QDialog(parent), m_impl(std::make_unique<initial_impl>()) {

    m_ui = std::make_unique<Ui::initial>();
    m_ui->setupUi(this);

    // btn1 apre popup
    connect(m_ui->btn1,&QPushButton::clicked,this,[this](){
        slotA();
    });

    // btn2 apre 2 popup con due slot differenti
    connect(m_ui->btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
    });

    // btn3 incrementa counter e quando arriva a N esce popup
    auto btn3_lambda = [this](){
        m_impl->incrementCounter();
        m_ui->counterValueLabel->setText(QString::number(this->m_impl->getCounter()));
        qDebug() <<"Btn 3 -> Counter: " << m_impl->getCounter();
        if(m_impl->getCounter() > constant::N){
            this ->alertLimiteCounter();
        }
    };

    connect(m_ui->btn3,&QPushButton::clicked,this,[this,btn3_lambda](){
        btn3_lambda();
    });

    connect(m_ui->setCounterBtn,&QPushButton::clicked,this,[this](){
        m_impl->setCounter(m_ui->spinBox->value());
        m_ui->counterValueLabel->setText(QString::number(this->m_impl->getCounter()));
    });
    
    connect(this,&initial::alertLimiteCounter,this,&initial::slotD);

    auto setCounterValue = [this](int value){
        m_impl->setCounter(value);
        m_ui->counterValueLabel->setText(QString::number(m_impl->getCounter()));
        this->accept();
    };

    // setcounter manuale
    connect(m_ui->dialogConfirmBtn, &QDialogButtonBox::clicked, this, [setCounterValue,this](){
        setCounterValue(m_ui->spinBox->value());
    });
}; // costruttore

initial::~initial(){

}

void initial::slotA(){
    QMessageBox::information(this,"Msg1","Btn1 - Slot A");
}
void initial::slotB(){
    QMessageBox::information(this,"Msg2","btn2 - Slot B");
}
void initial::slotC(){
    QMessageBox::information(this,"Msg3","Btn2 - Slot C");
}
void initial::slotD(){
    QMessageBox::warning(this,"Alert counter","Errore: counter raggiunto");
}