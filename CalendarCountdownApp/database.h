// database/database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QList>
#include "event.h"

class Database
{
public:
    Database(const QString &path);
    ~Database();

    bool initialize();
    bool addEvent(const Event &event);
    QList<Event> getEventsByDate(const QString &date);
    Event getNextEvent();
    QList<Event> getAllEvents();

private:
    QSqlDatabase db;
    bool createTable();
};

#endif // DATABASE_H
