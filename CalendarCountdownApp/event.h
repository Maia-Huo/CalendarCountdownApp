
/*=================================================*/

#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <QVariant>


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

