#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>

namespace Ui{
    class initial;
}

class initial : public QDialog {
    Q_OBJECT

    signals:
        void alertLimiteCounter();
        void setCounter();
        void resetCounter(int value);
        void retry();

    private slots:
        void slotA();
        void slotB();
        void slotC();
        void slotD();


    public:
        explicit initial (QWidget * parent = nullptr);
        ~initial();
    private:
        class initial_impl;
        std::unique_ptr<initial_impl> m_impl;
        std::unique_ptr<Ui::initial> m_ui;
};