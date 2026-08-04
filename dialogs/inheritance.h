#pragma once
#include <QDialog>
#include "inheritance/DerivedClass.h"

namespace Ui{
    class inheritance;
}

class inheritance : public QDialog {
    Q_OBJECT

    public: 
        explicit inheritance(QWidget *parent = nullptr);
        ~inheritance();

    public slots:
        void cast_implementation();
        
    private:
        class inheritance_impl; // forward declaration
        std::unique_ptr<inheritance_impl> m_impl;
        std::unique_ptr<Ui::inheritance> m_ui;
};