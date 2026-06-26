# pragma once

#include <QObject>
#include <QString>
#include <QDebug>

// class BaseClass : public QObject {
class BaseClass {
    // Q_OBJECT
    
    public:
    // explicit BaseClass(QObject * parent=nullptr);
    

    virtual ~BaseClass();
    // item 32: quando si eredita, va ereditato tutto, altrimenti si trovano altre soluzioni

    public:
    // item 33: non nascondere inherited names
    // -> soluzione: "using" per dare alla classe Derived tutti i metodi con lo stesso nome
    virtual void stampaPopup();
    virtual void stampaPopup(int x);

    // item 34: eredito solo interfaccia e non implementazione (in questo caso)
    virtual void stampaPopup(QString s) = 0;

    // item 36: non ridefinire una funzione non virtuale
    void stampaPopupNonVirtual();

    // item 37
    

    // item 38
};