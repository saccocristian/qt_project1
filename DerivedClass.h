#pragma once

#include "BaseClass.h"

class DerivedClass : public BaseClass {
    Q_OBJECT
    public:
        // item 33
        DerivedClass();
        using BaseClass::stampaPopup;

        void stampaPopup(QString s) override;

};