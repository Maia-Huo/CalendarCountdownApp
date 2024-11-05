

/*22222222222222222222222222222222222222222222222222*/


#include "event.h"

// 构造函数的定义
Event::Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description)
    : title(title), dateTime(dateTime), category(category), description(description) {}

// 方法定义
QString Event::getTitle() const { return title; }
QDateTime Event::getDateTime() const { return dateTime; }
QString Event::getCategory() const { return category; }
QString Event::getDescription() const { return description; }
QTime Event::getRemindTime() const { return remindTime; }

// setter 方法实现
void Event::setTitle(const QString &title) { this->title = title; }
void Event::setDateTime(const QDateTime &dateTime) { this->dateTime = dateTime; }
void Event::setCategory(const QString &category) { this->category = category; }
void Event::setDescription(const QString &description) { this->description = description; }
void Event::setRemindTime(const QTime &remindTime) { this->remindTime = remindTime; } // 如果需要
