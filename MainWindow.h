#pragma once

#include "inheritance/DerivedClass.h"
#include "singleton/CalculatorSingleton.h"
#include "dialogs/dialog_widgets.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <memory>
#include <QLabel>
#include <QString>

namespace my_project {
    static constexpr int N = 20;
}

namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT // per usare moc (meta-object compiler)

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    signals:
        void alertLimiteCounter();
        void setCounter();
        void resetCounter(int value);
        void retry();
    
    private slots:
        void receive_data(const Widget_dialog_data &data);
    private:
        // forward declaration
        class MainWindowImpl;
        
        // il ptr e' un tipo completo, ovvero la dimensione di un ptr e' nota e fissa
        std::unique_ptr<MainWindowImpl> impl;

        std::unique_ptr<Ui::MainWindow> m_ui; // "MainWindow" deriva dal nome di QMainWindow dentro QtDesigner

        static void printFunctionExample();
};