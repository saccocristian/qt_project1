#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <memory>

namespace my_project {
    static constexpr int N = 20;
}

namespace Ui{
    class MainWindow;
    class Dialog;
    class DialogString;
}

class FinestraPrincipale : public QMainWindow {
    Q_OBJECT // per usare moc (meta-object compiler)

    public:
        explicit FinestraPrincipale(QWidget *parent = nullptr);
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
        // void createDialogString();
        
    private:
        // forward declaration
        class FinestraPrincipaleImpl;
        
        // il ptr e' un tipo completo, ovvero la dimensione di un ptr e' nota e fissa
        std::unique_ptr<FinestraPrincipaleImpl> impl;

        std::unique_ptr<Ui::MainWindow> m_ui; // "MainWindow" deriva dal nome di QMainWindow dentro QtDesigner
        std::unique_ptr<Ui::Dialog> m_dialog;
        //std::unique_ptr<Ui::DialogString> m_dialogString;
    };