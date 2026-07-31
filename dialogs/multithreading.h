#pragma once
#include <QDialog>
#include <QCloseEvent>

namespace Ui{
    class multithreading;
}

class multithreading : public QDialog {
    Q_OBJECT

    public:
        explicit multithreading(QWidget * parent = nullptr);
        ~multithreading();

    protected:
        void closeEvent(QCloseEvent *event) override;

    signals:
        void cleanup();
        void retry();
    private slots:
        void startThread();

    private:
        class multithreading_impl;
        std::unique_ptr<multithreading_impl> m_impl;
        std::unique_ptr<Ui::multithreading> m_ui;
        
};