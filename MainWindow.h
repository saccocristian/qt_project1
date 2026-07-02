#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <memory>
#include <QLabel>
#include <QString>
#include "inheritance/DerivedClass.h"
#include "singleton/Calculator.h"

namespace my_project {
    static constexpr int N = 20;
}

namespace Ui{
    class MainWindow;
    class DCounter;
    class DString;
    class DCheckbox;
}

class MainWindow : public QMainWindow {
    Q_OBJECT // per usare moc (meta-object compiler)

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent *event) override;

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
        void slotE();
        void createDialogCounter();
        void createDialogString();
        void createDialogCheckbox();
        void showPicture();
        
    private:
        // forward declaration
        class MainWindowImpl;
        
        // il ptr e' un tipo completo, ovvero la dimensione di un ptr e' nota e fissa
        std::unique_ptr<MainWindowImpl> impl;

        std::unique_ptr<Ui::MainWindow> m_ui; // "MainWindow" deriva dal nome di QMainWindow dentro QtDesigner
        std::unique_ptr<Ui::DCounter> m_dialogCounter;
        std::unique_ptr<Ui::DString> m_dialogString;
        std::unique_ptr<Ui::DCheckbox> m_dialogCheckbox;

        static void printFunctionExample();
    };