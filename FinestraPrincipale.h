#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QPointer>

#include <memory.h>

#include "MyBtn.h"
#include "MyThread.h"
#include "Worker.h"
namespace my_project {
    static constexpr int N = 20;
}

/* Funzionamento:
- btn1 -> 1 slot A
- btn2 -> 1 slot B + 1 slot C
- btn3 -> 1 slot D
- btn4 -> chiude app
- btn5 -> thread loading bar
*/

class FinestraPrincipale : public QWidget {
    Q_OBJECT // per usare moc (meta-object compiler)

    signals:
        void alertLimiteCounter();
        
    private slots:
        void slotA();
        void slotB();
        void slotC();
        void slotD();
        void slotE();

    public:
    // Costruttore
    explicit FinestraPrincipale(QWidget *parent = nullptr);
    //Distruttore
    ~FinestraPrincipale();

    private:
        int counter{0};

        QPointer<QVBoxLayout> layoutPrincipale;
        //QPointer
    
        QPointer<MyBtn> btn1;
        QPointer<MyBtn> btn2;
        QPointer<MyBtn> btn3;
        QPointer<MyBtn> btn4;
        QPointer<MyBtn> btn5;
        QPointer<QProgressBar> m_progressBar;


        
};