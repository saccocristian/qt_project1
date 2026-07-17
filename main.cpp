#include "MainWindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
class Foo {
    public:
    ~Foo(){
        qDebug() << "~ Classe Foo";
    }
};

int main(int argc, char *argv[]){
    
    Foo myFoo;
    
    QApplication app (argc,argv);
    
    MainWindow window;
    //finestra.setAttribute(Qt::WA_DeleteOnClose);
    window.show();

    // main event loop non ancora partito
    qDebug() << "--- Main Event Loop: Inizio ---";
    qDebug() << "Main.cpp -- ThreadId: " << QThread::currentThreadId();

    int app_res = app.exec();
    
    qDebug() << "--- Main Event Loop: Fine ---";
    return app_res;
}

// modifica 3
// modifica 4