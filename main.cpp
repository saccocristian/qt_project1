#include "FinestraPrincipale.h"
#include <QApplication>
#include <QThread>

class Foo {
    public:
    ~Foo(){
        qDebug() << "~ Classe Foo";
    }
};

int main(int argc, char *argv[]){
    
    Foo myFoo;
    
    QApplication app (argc,argv);
    
    FinestraPrincipale finestra;
    //finestra.setAttribute(Qt::WA_DeleteOnClose);
    finestra.show();

    // main event loop non ancora partito
    qDebug() << "--- Main Event Loop: Inizio ---";
    qDebug() << "Main.cpp -- ThreadId: " << QThread::currentThreadId();

    int app_res = app.exec();
    
    qDebug() << "--- Main Event Loop: Fine ---";
    return app_res;
}