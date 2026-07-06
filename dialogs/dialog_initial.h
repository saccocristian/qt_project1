#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>

namespace Ui{
    class d_initial;
}

class dialog_initial : public QDialog {
    Q_OBJECT

    signals:
        void alertLimiteCounter();
        void cleanup();
        void setCounter();
        void resetCounter(int value);
        void retry();

    private slots:
        void slotA();
        void slotB();
        void slotC();
        void slotD();


    public:
        explicit dialog_initial (QWidget * parent = nullptr);
        ~dialog_initial();
    private:
        class dialog_initial_impl;
        std::unique_ptr<dialog_initial_impl> m_impl;
        std::unique_ptr<Ui::d_initial> m_ui;
};