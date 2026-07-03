#pragma once
#include <QDialog>
#include <QCloseEvent>

namespace Ui{
    class d_multithreading;
}

class dialog_multithreading : public QDialog {
    Q_OBJECT

    public:
        explicit dialog_multithreading(QWidget * parent = nullptr);
        ~dialog_multithreading();

    protected:
        void dialog_multithreading::closeEvent(QCloseEvent *event) override;

    private slots:
        void startThread();
        
    private:
        class dialog_multithreading_impl;
        std::unique_ptr<dialog_multithreading_impl> m_impl;
        std::unique_ptr<Ui::d_multithreading> m_ui;
        
};