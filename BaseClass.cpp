#include "BaseClass.h"

// BaseClass::BaseClass(QObject * parent) : QObject(parent){

// }

BaseClass::~BaseClass(){
    qDebug() << "Distruttore Base Class";
}
void BaseClass::stampaPopup(){
    qDebug() << "BaseClass::stampaPopup() --- (virtual)";
}

void BaseClass::stampaPopup(int x){
    qDebug() << "BaseClass::stampaPopup(int x) --- (virtual) -> Valore inserito: " << x;
}

void BaseClass::stampaPopupNonVirtual(){
    qDebug() << "BaseClass::creationPopup() (no virtual)";
}