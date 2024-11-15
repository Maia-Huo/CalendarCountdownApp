#ifndef SQLITESTORAGE_H
#define SQLITESTORAGE_H

#include "event.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QSqlError>
#include <QDebug>

class SQLiteStorage {
public:
    SQLiteStorage();
    ~SQLiteStorage();

    // 添加事件
    void addEvent(const QString &title, const QDateTime &dateTime,
                  const QString &category, const QString &description,
                  const QTime &remindTime);
    QVector<Event> getAllEvents();            //从数据库获取所有事件
    void deleteEvent(const QString &title);   //删除日历事件
    void updateEvent(const Event &event);     //编辑日历事件

private:
    QSqlDatabase db;
};

#endif // SQLITESTORAGE_H
