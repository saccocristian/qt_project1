#include "Calculator.h"
#include <QDebug>

CalculatorSingleton* CalculatorSingleton::m_calculator_instance = nullptr;

CalculatorSingleton::CalculatorSingleton(){
}

CalculatorSingleton * CalculatorSingleton::getInstance(){
    if(m_calculator_instance==nullptr){
        m_calculator_instance = new CalculatorSingleton();
    }
    m_calculator_instance->m_state = true;
    return m_calculator_instance;
}

void CalculatorSingleton::printState() {
    qDebug() << "Calculator on? " << this->m_state;
}

void CalculatorSingleton::increaseCounter(){
    ++this->m_counter;
}

int CalculatorSingleton::getCounter(){
    return this->m_counter;
}

void CalculatorSingleton::printCounter(){
    qDebug() << "Calculator counter: " << this->m_counter;
}