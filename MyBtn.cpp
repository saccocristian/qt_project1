#include "MyBtn.h"

MyBtn::~MyBtn(){
    qDebug() << "~ MyBtn : " << this->objectName();
}