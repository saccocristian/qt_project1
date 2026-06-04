#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QThread>
#include <QProgressBar>

namespace my_project {
    static constexpr int N = 20;
}
/*
Funzionamento base
---
4 pulsanti
- btn1 -> 1 slot A
- btn2 -> 1 slot B + 1 slot C
- btn3 -> 1 slot D
- btn4 -> chiude app
' btn5 -> simula sleep 5s
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
    FinestraPrincipale(QWidget *parent = nullptr);

    private:
        int counter = 0;
        QProgressBar *m_progressBar;

};