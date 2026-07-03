#pragma once
#include <QDialog>

namespace Ui{
    class d_inheritance;
}

class dialog_inheritance : public QDialog {
    Q_OBJECT

    public: 
        explicit dialog_inheritance(QWidget *parent = nullptr);
        ~dialog_inheritance();
    private:
        class dialog_inheritance_impl; // forward declaration
        std::unique_ptr<dialog_inheritance_impl> m_inheritance_impl;
        std::unique_ptr<Ui::d_inheritance> m_inheritance_ui;
};