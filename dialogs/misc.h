#pragma once
#include <QDialog>
#include "singleton/CalculatorSingleton.h"

namespace Ui{
    class misc;
}

class misc : public QDialog {
    Q_OBJECT

    public:
        explicit misc(QWidget * parent = nullptr);
        ~misc();
    private:
        class misc_impl;
        std::unique_ptr<misc_impl> m_impl;
        std::unique_ptr<Ui::misc> m_ui;

};