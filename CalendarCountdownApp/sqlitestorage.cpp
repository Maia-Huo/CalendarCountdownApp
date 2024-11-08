#include "event.h"
#include "sqlitestorage.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SQLiteStorage::SQLiteStorage() {
    db = QSqlDatabase::addDatabase("QSQLITE");//添加一个 SQLite 数据库驱动
    db.setDatabaseName("data.db");//设置数据库文件名为data.db，在当前工作目录中创建或打开该文件

    if (!db.open()) {//尝试打开数据库
        qDebug() << "Error opening database:" << db.lastError().text();
    }

    // 创建表
    //如果表不存在，则创建一个新的表
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS events ("
                "title TEXT NOT NULL, "
                "dateTime TEXT NOT NULL, "
                "category TEXT, "
                "description TEXT)");
}

SQLiteStorage::~SQLiteStorage() {//关闭数据库连接
    db.close();
}

//添加新事件到数据库
void SQLiteStorage::addEvent(const QString &title, const QDateTime &dateTime,
                             const QString &category, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO events (title, dateTime, category, description) "
                  "VALUES (:title, :dateTime, :category, :description)");

    query.bindValue(":title", title);
    query.bindValue(":dateTime", dateTime.toString(Qt::ISODate));
    query.bindValue(":category", category);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Error adding event:" << query.lastError().text();
    }
}

//从数据库获取所有事件
QVector<Event> SQLiteStorage::getAllEvents() {
    QVector<Event> events;
    QSqlQuery query("SELECT title, dateTime, category, description FROM events");

    while (query.next()) {
        QString title = query.value(0).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(1).toString(), Qt::ISODate);
        QString category = query.value(2).toString();
        QString description = query.value(3).toString();

        events.append(Event(title, dateTime, category, description));
    }

    return events;
}

//从数据库删除选中事件
void SQLiteStorage::deleteEvent(const QString &title) {
    QSqlQuery query;
    query.prepare("DELETE FROM events WHERE title = :title");
    query.bindValue(":title", title);

    if (!query.exec()) {
        qDebug() << "Error deleting event:" << query.lastError().text();
    } else {
        qDebug() << "Event deleted successfully:" << title;
    }
}

//更新编辑后的事件
void SQLiteStorage::updateEvent(const Event &event) {
    QSqlQuery query;
    query.prepare("UPDATE events SET dateTime = :dateTime, category = :category, description = :description WHERE title = :title");

    query.bindValue(":title", event.getTitle());
    query.bindValue(":dateTime", event.getDateTime().toString(Qt::ISODate));
    query.bindValue(":category", event.getCategory());
    query.bindValue(":description", event.getDescription());

    if (!query.exec()) {
        qDebug() << "Error updating event:" << query.lastError().text();
    } else {
        qDebug() << "Event updated successfully:" << event.getTitle();
    }
}
