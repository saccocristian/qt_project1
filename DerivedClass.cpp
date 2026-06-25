#include "DerivedClass.h"
    // item 33

    DerivedClass::DerivedClass(){

    }

    void DerivedClass::stampaPopup(QString s){
        qDebug() << "DerivedClass::stampaPopup() --- (virtual)";

        qDebug() << s;
    }


    /*
    Metodo creato intenzionalmente: non si puo' fare override di una funzione
    che non e' dichiarata virtual!
    */

    // void DerivedClass::stampaPopupNonVirtual(){
    // }
