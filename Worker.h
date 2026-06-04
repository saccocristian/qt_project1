#pragma once
#include <QObject>

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(QObject *parent = nullptr);

public slots:
    void doWork();       // il lavoro pesante (il loop con sleep)

signals:
    void progress(int percent);
    void finished(const QString &result);
};