#pragma once

#include "BaseClass.h"

// con final interrompo ereditarieta' 
class DerivedClass final : public BaseClass {
    // Q_OBJECT
    public:
        // item 33
        // explicit DerivedClass(QObject * parent=nullptr);
        ~DerivedClass();
        using BaseClass::stampaPopup;

        void stampaPopup(QString s) override;

};