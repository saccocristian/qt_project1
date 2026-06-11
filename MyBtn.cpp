#include "MyBtn.h"

MyBtn::~MyBtn(){
    qDebug() << "Distruttore -> MyBtn : " << this->objectName();
}