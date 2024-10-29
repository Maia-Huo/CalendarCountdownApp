// utils/notifier.h
#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include "database/database.h"

class Notifier : public QObject
{
    Q_OBJECT
public:
    Notifier(QObject *parent = nullptr);
    ~Notifier();
    void start();

private:
    QThread workerThread;
    Database db;

    void process();

signals:
    void notify(const QString &title, const QString &message);
};

#endif // NOTIFIER_H
