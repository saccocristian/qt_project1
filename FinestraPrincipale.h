#pragma once

#include <QMainWindow>
#include <QCloseEvent>

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
        class FinestraPrincipaleImpl;
        FinestraPrincipaleImpl * impl;

};