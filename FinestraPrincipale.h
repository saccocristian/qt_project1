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
    explicit FinestraPrincipale(QWidget *parent = nullptr);

    //Distruttore
    ~FinestraPrincipale();

    private:
        int counter{0};
        // QProgressBar *m_progressBar{nullptr};

        /* 
        Commento ridondante: creo un ptr grazie alla funzione make_unique, 
        cosi da poter passare come argomento l'argomento che 
        andrebbe all'oggetto senza doverne creare uno nuovo.
        Senza usare make_unique, dovrei fare new e creare un oggetto QProgressBar
        con argomento nullptr (che e' il parent della progress bar)
        */
        std::unique_ptr<QProgressBar> m_progressBar;

};