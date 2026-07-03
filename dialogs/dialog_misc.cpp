#include "dialog_misc.h"
#include "ui_d_misc.h"
#include "singleton/CalculatorSingleton.h"

#include <QDebug>

class dialog_misc::dialog_misc_impl {
    public:

    private:
        
};

dialog_misc::dialog_misc(QWidget * parent) : QDialog(parent),m_misc_impl(std::make_unique<dialog_misc_impl>()) {
    
    m_misc_ui = std::make_unique<Ui::d_misc>();
    m_misc_ui->setupUi(this);

    // // ptr to function
    // void ( * ptrFunction)() = dialog_misc::printFunctionExample;
    // connect(misc_ui->btn1,&QPushButton::clicked,this,[this,ptrFunction](){
    //     ptrFunction();
    // });

    // CalculatorSingleton * calculator = CalculatorSingleton::getInstance();

    // CalculatorSingleton * calculator_copy = CalculatorSingleton::getInstance();
}; // costruttore

dialog_misc::~dialog_misc(){
    
};

void dialog_misc::printFunctionExample(){
    qDebug() << "Usage of ptr to function";
}