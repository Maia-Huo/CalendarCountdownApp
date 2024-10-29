// database/database.cpp
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDateTime>
#include <QDebug>

Database::Database(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

Database::~Database()
{
    if (db.isOpen())
        db.close();
}

bool Database::initialize()
{
    if (!db.open())
    {
        qDebug() << "无法连接到数据库:" << db.lastError().text();
        return false;
    }
    return createTable();
}

bool Database::createTable()
{
    QSqlQuery query;
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS events (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            date TEXT NOT NULL,
            time TEXT,
            category TEXT,
            remind_time TEXT,
            description TEXT
        )
    )";
    if (!query.exec(createTableSQL))
    {
        qDebug() << "创建表失败:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::addEvent(const Event &event)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO events (title, date, time, category, remind_time, description)
        VALUES (:title, :date, :time, :category, :remind_time, :description)
    )");
    query.bindValue(":title", event.title);
    query.bindValue(":date", event.date);
    query.bindValue(":time", event.time);
    query.bindValue(":category", event.category);
    query.bindValue(":remind_time", event.remindTime);
    query.bindValue(":description", event.description);

    if (!query.exec())
    {
        qDebug() << "添加事件失败:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Event> Database::getEventsByDate(const QString &date)
{
    QList<Event> events;
    QSqlQuery query;
    query.prepare("SELECT * FROM events WHERE date = :date ORDER BY time ASC");
    query.bindValue(":date", date);
    if (query.exec())
    {
        while (query.next())
        {
            Event event;
            event.id = query.value("id").toInt();
            event.title = query.value("title").toString();
            event.date = query.value("date").toString();
            event.time = query.value("time").toString();
            event.category = query.value("category").toString();
            event.remindTime = query.value("remind_time").toString();
            event.description = query.value("description").toString();
            events.append(event);
        }
    }
    else
    {
        qDebug() << "获取事件失败:" << query.lastError().text();
    }
    return events;
}

Event Database::getNextEvent()
{
    Event nextEvent;
    QSqlQuery query;
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
    query.prepare(R"(
        SELECT * FROM events
        WHERE datetime(date || ' ' || time) >= datetime(:current)
        ORDER BY datetime(date || ' ' || time) ASC
        LIMIT 1
    )");
    query.bindValue(":current", currentDateTime);
    if (query.exec())
    {
        if (query.next())
        {
            nextEvent.id = query.value("id").toInt();
            nextEvent.title = query.value("title").toString();
            nextEvent.date = query.value("date").toString();
            nextEvent.time = query.value("time").toString();
            nextEvent.category = query.value("category").toString();
            nextEvent.remindTime = query.value("remind_time").toString();
            nextEvent.description = query.value("description").toString();
        }
    }
    else
    {
        qDebug() << "获取下一个事件失败:" << query.lastError().text();
    }
    return nextEvent;
}

QList<Event> Database::getAllEvents()
{
    QList<Event> events;
    QSqlQuery query("SELECT * FROM events ORDER BY datetime(date || ' ' || time) ASC");
    while (query.next())
    {
        Event event;
        event.id = query.value("id").toInt();
        event.title = query.value("title").toString();
        event.date = query.value("date").toString();
        event.time = query.value("time").toString();
        event.category = query.value("category").toString();
        event.remindTime = query.value("remind_time").toString();
        event.description = query.value("description").toString();
        events.append(event);
    }
    return events;
}
