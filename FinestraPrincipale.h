#pragma once

#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include <QVBoxLayout>
#include<QDebug>

class FinestraPrincipale : public QWidget {
    Q_OBJECT // per usare moc (meta-object compiler)

    public:
    FinestraPrincipale(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Mac Shortcuts Dashboard");
        resize(500,250);

        QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);

        /*
        Parte superiore
        FinestraPrincipale
            layoutPrincipale
                barraSuperiore
                    layoutBarra
                        btnBrave
                        ...
                barraInferiore
        */

        QWidget *barraSuperiore = new QWidget(this);
        QHBoxLayout *layoutBarra = new QHBoxLayout(barraSuperiore);

        QPushButton *btnBrave = new QPushButton("Brave", this);
        QPushButton *btnVscode = new QPushButton("VS Code", this);
        QPushButton *btnSpotify = new QPushButton("Spotify", this);
        QPushButton *btnGeneral = new QPushButton("General", this);

        layoutBarra->addWidget(btnBrave);
        layoutBarra->addWidget(btnVscode);
        layoutBarra->addWidget(btnSpotify);
        layoutBarra->addWidget(btnGeneral);

        layoutPrincipale->addWidget(barraSuperiore);
        
        pannelloBrave = new QWidget(this);
        QHBoxLayout *layBrave = new QHBoxLayout(pannelloBrave);
        QPushButton *btnRicarica = new QPushButton("Ricarica",pannelloBrave);
        QPushButton *btnNewTab = new QPushButton("New Tab",pannelloBrave);
        layBrave->addWidget(btnRicarica);
        layBrave->addWidget(btnNewTab);

        pannelloVscode = new QWidget(this);
        QHBoxLayout *layVscode = new QHBoxLayout(pannelloVscode);
        QPushButton *btnSalva = new QPushButton("Salva",pannelloVscode);
        QPushButton *btnTerminale = new QPushButton("Terminale",pannelloVscode);
        layVscode->addWidget(btnSalva);
        layVscode->addWidget(btnTerminale);

        pannelloSpotify = new QWidget(this);
        QHBoxLayout *laySpotify = new QHBoxLayout(pannelloSpotify);
        QPushButton *btnPrev = new QPushButton("Prev",pannelloSpotify);
        QPushButton *btnPlay = new QPushButton("Play/Pause",pannelloSpotify);
        QPushButton *btnNext = new QPushButton("Next",pannelloSpotify);
        laySpotify->addWidget(btnPrev);
        laySpotify->addWidget(btnPlay);
        laySpotify->addWidget(btnNext);

        pannelloGeneral = new QWidget(this);
        QHBoxLayout *layGeneral = new QHBoxLayout(pannelloGeneral);
        QPushButton *btnStop = new QPushButton("Stop",pannelloGeneral);
        QPushButton *btnVolPiu = new QPushButton("Vol +",pannelloGeneral);
        QPushButton *btnVolMeno = new QPushButton("Vol -", pannelloGeneral);
        layGeneral->addWidget(btnStop);
        layGeneral->addWidget(btnVolPiu);
        layGeneral->addWidget(btnVolMeno);

        layoutPrincipale->addWidget(pannelloBrave);
        layoutPrincipale->addWidget(pannelloVscode);
        layoutPrincipale->addWidget(pannelloSpotify);
        layoutPrincipale->addWidget(pannelloGeneral);

        mostraSoloPannello(pannelloBrave);

        // Signals e slots per 4 bottoni principali
        connect(btnBrave, &QPushButton::clicked, this, [this]() {
            mostraSoloPannello(pannelloBrave);
        });
        connect(btnVscode,&QPushButton::clicked,this,[this](){
            mostraSoloPannello(pannelloVscode);
        });
        connect(btnSpotify,&QPushButton::clicked,this,[this](){
            mostraSoloPannello(pannelloSpotify);
        });
        connect(btnGeneral,&QPushButton::clicked,this,[this](){
            mostraSoloPannello(pannelloGeneral);
        });

        // Connessioni (fittizie) per app
        connect(btnRicarica, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+R a Brave"; });
        connect(btnNewTab, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+T a Brave"; });
        connect(btnSalva, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+S a VS Code"; });
        connect(btnTerminale, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Ctrl+Shift+T a VS Code"; });
    }

    private:
    // Puntatori ai nostri 4 pannelli per poterli mostrare/nascondere
    QWidget *pannelloBrave;
    QWidget *pannelloVscode;
    QWidget *pannelloSpotify;
    QWidget *pannelloGeneral;

    void mostraSoloPannello(QWidget *pannelloDaMostrare) {
        pannelloBrave->hide();
        pannelloVscode->hide();
        pannelloSpotify->hide();
        pannelloGeneral->hide();
        
        pannelloDaMostrare->show();
    }
};