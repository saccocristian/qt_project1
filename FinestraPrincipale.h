#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget> // Nuovo componente per gestire le pagine
#include <QDebug>

class FinestraPrincipale : public QWidget {
    Q_OBJECT // per usare moc (meta-object compiler)

    signals:
        void categoriaCambiata(const QString &nomeCategoria);
    private slots:
        void cambiaCategoria() {
            QPushButton *btn = qobject_cast<QPushButton*>(sender());
            if (!btn) return;
            QString nome = btn->text();
            if (nome == "Brave")      mostraSoloPannello(pannelloBrave);
            else if (nome == "VS Code")    mostraSoloPannello(pannelloVscode);
            else if (nome == "Spotify")    mostraSoloPannello(pannelloSpotify);
            else if (nome == "General")    mostraSoloPannello(pannelloGeneral);

            emit categoriaCambiata(nome);
        }

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
        
        // Brave 2 pulsanti
        pannelloBrave = new QWidget(this);
        QHBoxLayout *layBrave = new QHBoxLayout(pannelloBrave);
        QPushButton *btnRicarica = new QPushButton("Ricarica",pannelloBrave);
        QPushButton *btnNewTab = new QPushButton("New Tab",pannelloBrave);
        layBrave->addWidget(btnRicarica);
        layBrave->addWidget(btnNewTab);

        // VS code 2 pulsanti
        pannelloVscode = new QWidget(this);
        QHBoxLayout *layVscode = new QHBoxLayout(pannelloVscode);
        QPushButton *btnSalva = new QPushButton("Salva",pannelloVscode);
        QPushButton *btnTerminale = new QPushButton("Terminale",pannelloVscode);
        layVscode->addWidget(btnSalva);
        layVscode->addWidget(btnTerminale);

        // Spotify 3 pulsanti
        pannelloSpotify = new QWidget(this);
        QHBoxLayout *laySpotify = new QHBoxLayout(pannelloSpotify);
        QPushButton *btnPrev = new QPushButton("Prev",pannelloSpotify);
        QPushButton *btnPlay = new QPushButton("Play/Pause",pannelloSpotify);
        QPushButton *btnNext = new QPushButton("Next",pannelloSpotify);
        laySpotify->addWidget(btnPrev);
        laySpotify->addWidget(btnPlay);
        laySpotify->addWidget(btnNext);

        // General 3 pulsanti
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
        connect(btnBrave,   &QPushButton::clicked, this, &FinestraPrincipale::cambiaCategoria);
        connect(btnVscode,  &QPushButton::clicked, this, &FinestraPrincipale::cambiaCategoria);
        connect(btnSpotify, &QPushButton::clicked, this, &FinestraPrincipale::cambiaCategoria);
        connect(btnGeneral, &QPushButton::clicked, this, &FinestraPrincipale::cambiaCategoria);
        
        connect(this, &FinestraPrincipale::categoriaCambiata,
        this, &QWidget::setWindowTitle);

        // Connessioni (fittizie) per app
        connect(btnRicarica, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+R a Brave"; });
        connect(btnNewTab, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+T a Brave"; });
        connect(btnSalva, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Command+S a VS Code"; });
        connect(btnTerminale, &QPushButton::clicked, []() { qDebug() << "Eseguo: Invia Ctrl+Shift+T a VS Code"; });
    }

    private:

        void mostraSoloPannello(QWidget *pannelloDaMostrare) {
            pannelloBrave->hide();
            pannelloVscode->hide();
            pannelloSpotify->hide();
            pannelloGeneral->hide();
            
            pannelloDaMostrare->show();
        }

        // Puntatori ai nostri 4 pannelli per poterli mostrare/nascondere
        QWidget *pannelloBrave;
        QWidget *pannelloVscode;
        QWidget *pannelloSpotify;
        QWidget *pannelloGeneral;
        
};