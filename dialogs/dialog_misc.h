#pragma once
#include <QDialog>
#include "singleton/CalculatorSingleton.h"

namespace Ui{
    class d_misc;
}

class dialog_misc : public QDialog {
    Q_OBJECT

    public:
        explicit dialog_misc(QWidget * parent = nullptr);
        ~dialog_misc();
    private:
        class dialog_misc_impl;
        std::unique_ptr<dialog_misc_impl> m_impl;
        std::unique_ptr<Ui::d_misc> m_ui;

};