//#ifndef EVENT_H
//#define EVENT_H

//#include <QString>
//#include <QDateTime>

//class Event {
//public:
//    Event(const QString &title, const QDateTime &dateTime, const QString &category);

//    QString getTitle() const;
//    QDateTime getDateTime() const;
//    QString getCategory() const;

//private:
//    QString title;
//    QDateTime dateTime;
//    QString category; // 事件分类
//};

//#endif // EVENT_H


// event.h
#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>

class Event {
public:
    Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description);

    QString getTitle() const;
    QDateTime getDateTime() const;
    QString getCategory() const;
    QString getDescription() const;

private:
    QString title;
    QDateTime dateTime;
    QString category;
    QString description;
};

#endif // EVENT_H





