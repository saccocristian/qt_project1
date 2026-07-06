#include "dialog_misc.h"
#include "ui_d_misc.h"
#include "singleton/CalculatorSingleton.h"

#include <QDebug>

void printFunctionExample();

class dialog_misc::dialog_misc_impl {
    public:

    private:
        
};

dialog_misc::dialog_misc(QWidget * parent) : QDialog(parent),m_impl(std::make_unique<dialog_misc_impl>()) {
    
    m_ui = std::make_unique<Ui::d_misc>();
    m_ui->setupUi(this);

    // ptr to function
    void ( * ptrFunction)() = printFunctionExample;
    connect(m_ui->btn1,&QPushButton::clicked,this,[this,ptrFunction](){
        ptrFunction();
    });

    CalculatorSingleton * calculator = CalculatorSingleton::getInstance();
    CalculatorSingleton * calculator_copy = CalculatorSingleton::getInstance();

    auto calculator_fn = [](CalculatorSingleton * calculator){
        calculator ->increaseCounter();
        calculator ->printCounter();
    };
    void (*ptr_calculator_fn)(CalculatorSingleton *) = calculator_fn;

    connect(m_ui->btn2,&QPushButton::clicked,this,[calculator,ptr_calculator_fn](){
        ptr_calculator_fn(calculator);
    });

    connect(m_ui->btn3,&QPushButton::clicked,this,[calculator_copy,ptr_calculator_fn](){
        ptr_calculator_fn(calculator_copy);
    });
}; // costruttore

dialog_misc::~dialog_misc(){
    
};

void printFunctionExample(){
    qDebug() << "Usage of ptr to function";
}