#include "dialog_initial.h"
#include "ui_d_initial.h"

#include <QMessageBox>
#include <QDebug>

namespace constant{
    int N = 20;
}
class dialog_initial::dialog_initial_impl{

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

dialog_initial::dialog_initial(QWidget * parent) : QDialog(parent), m_initial_impl(std::make_unique<dialog_initial_impl>()) {

    m_initial_ui = std::make_unique<Ui::d_initial>();
    m_initial_ui->setupUi(this);

    // btn1 apre popup
    connect(m_initial_ui->btn1,&QPushButton::clicked,this,[this](){
        slotA();
    });

    // btn2 apre 2 popup con due slot differenti
    connect(m_initial_ui->btn2,&QPushButton::clicked,this,[this](){
        slotB();
        slotC();
    });

    // btn3 incrementa counter e quando arriva a N esce popup
    auto btn3_lambda = [this](){
        m_initial_impl->incrementCounter();
        m_initial_ui->counterValueLabel->setText(QString::number(this->m_initial_impl->getCounter()));
        qDebug() <<"Btn 3 -> Counter: " << m_initial_impl->getCounter();
        if(m_initial_impl->getCounter() > constant::N){
            this ->alertLimiteCounter();
        }
    };

    connect(m_initial_ui->btn3,&QPushButton::clicked,this,[this,btn3_lambda](){
        btn3_lambda();
    });

    connect(m_initial_ui->setCounterBtn,&QPushButton::clicked,this,[this](){
        m_initial_impl->setCounter(m_initial_ui->spinBox->value());
        m_initial_ui->counterValueLabel->setText(QString::number(this->m_initial_impl->getCounter()));
    });
    
    connect(this,&dialog_initial::alertLimiteCounter,this,&dialog_initial::slotD);

    auto setCounterValue = [this](int value){
        m_initial_impl->setCounter(value);
        m_initial_ui->counterValueLabel->setText(QString::number(m_initial_impl->getCounter()));
        this->accept();
    };

    // setcounter manuale
    connect(m_initial_ui->dialogConfirmBtn, &QDialogButtonBox::clicked, this, [setCounterValue,this](){
        setCounterValue(m_initial_ui->spinBox->value());
    });
}; // costruttore

dialog_initial::~dialog_initial(){

}

void dialog_initial::slotA(){
    QMessageBox::information(this,"Msg1","Btn1 - Slot A");
}
void dialog_initial::slotB(){
    QMessageBox::information(this,"Msg2","btn2 - Slot B");
}
void dialog_initial::slotC(){
    QMessageBox::information(this,"Msg3","Btn2 - Slot C");
}
void dialog_initial::slotD(){
    QMessageBox::warning(this,"Alert counter","Errore: counter raggiunto");
}