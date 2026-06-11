#pragma once
#include <QObject>
#include <QDebug>
class Worker : public QObject {

    Q_OBJECT
    
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void doWork();       // il lavoro pesante (il loop con sleep)

signals:
    void progress(int percent);
    void finished(const QString &result);
};