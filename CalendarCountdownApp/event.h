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
//#ifndef EVENT_H
//#define EVENT_H

//#include <QString>
//#include <QDateTime>

//class Event {
//public:
//    Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description);

//    QString getTitle() const;
//    QDateTime getDateTime() const;
//    QString getCategory() const;
//    QString getDescription() const;

//private:
//    QString title;
//    QDateTime dateTime;
//    QString category;
//    QString description;
//};

//#endif // EVENT_H

/*=================================================*/

#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QTime>

class Event {
public:
    Event() = default;
    Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description);

    QString getTitle() const;
    QDateTime getDateTime() const;
    QString getCategory() const;
    QString getDescription() const;
    QTime getRemindTime() const;

    // 添加 setter 方法
    void setTitle(const QString &title);
    void setDateTime(const QDateTime &dateTime);
    void setCategory(const QString &category);
    void setDescription(const QString &description);
    void setRemindTime(const QTime &remindTime); // 假设你需要这个

private:
    QString title;
    QDateTime dateTime;
    QString category;
    QString description;
    QTime remindTime; // 添加提醒时间成员变量
};

#endif // EVENT_H

/*22222222222222222222222222222222222222222222222222*/

