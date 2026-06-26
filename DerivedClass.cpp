#include "DerivedClass.h"
    // item 33

    // DerivedClass::DerivedClass(QObject * parent) : BaseClass(parent){

    // }

    void DerivedClass::stampaPopup(QString s){
        qDebug() << "DerivedClass::stampaPopup() --- (virtual)";

        qDebug() << s;
    }

    DerivedClass::~DerivedClass(){
        qDebug() << "Distruttore Derived Class";
    }
    /*
    Metodo creato intenzionalmente: non si puo' fare override di una funzione
    che non e' dichiarata virtual!
    */

    // void DerivedClass::stampaPopupNonVirtual(){
    // }
