#include "FinestraPrincipale.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication app (argc,argv);
    
    FinestraPrincipale finestra;
    finestra.show();

    return app.exec();
}