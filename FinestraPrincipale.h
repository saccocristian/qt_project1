#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QPointer>
#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QCloseEvent>

#include <memory.h>

#include "MyBtn.h"
#include "MyThread.h"
#include "Worker.h"
#include "MyDialog.h"

namespace my_project {
    static constexpr int N = 20;
}

/* Funzionamento:
- btn1 -> 1 slot A
- btn2 -> 1 slot B + 1 slot C
- btn3 -> 1 slot D
- btn4 -> chiude app
- btn5 -> thread loading bar
- btn6 -> imposta valore var "counter"
*/

class FinestraPrincipale : public QMainWindow {
    Q_OBJECT // per usare moc (meta-object compiler)

    public:
    // Costruttore
    explicit FinestraPrincipale(QMainWindow *parent = nullptr);
    //Distruttore
    ~FinestraPrincipale();

    protected:
        void closeEvent(QCloseEvent *event) override;

    signals:
        void alertLimiteCounter();
        void cleanup();
        void setCounter();
        void resetCounter(int value);
        
    private slots:
        void slotA();
        void slotB();
        void slotC();
        void slotD();
        void slotE();
        void createDialog();
        
    private:
        int counter{0};

        QPointer<QVBoxLayout> layoutPrincipale;

        QPointer<MyBtn> btn1;
        QPointer<MyBtn> btn2;
        QPointer<MyBtn> btn3;
        QPointer<MyBtn> btn4;
        QPointer<MyBtn> btn5;
        QPointer<MyBtn> btn6;
        QPointer<QProgressBar> m_progressBar;

        // Thread logics
        QPointer<MyThread> thread;
        QPointer<Worker> worker;
        
};