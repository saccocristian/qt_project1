#include "FinestraPrincipale.h"
#include <QApplication>

class Foo {
    public:
    ~Foo(){
        qDebug() << "Distruttore foo";
    }
};

int main(int argc, char *argv[]){
    
    Foo myFoo;
    
    QApplication app (argc,argv);
    
    FinestraPrincipale finestra;
    //finestra.setAttribute(Qt::WA_DeleteOnClose);
    finestra.show();
    // main event loop non ancora partito
    qDebug() << "Avvio Main Event Loop ...";
    int app_res = app.exec();
    
    qDebug() << "Main Event Loop terminato";
    return app_res;
}