//#include "event.h"

//Event::Event(const QString &title, const QDateTime &dateTime, const QString &category)
//    : title(title), dateTime(dateTime), category(category) {}

//QString Event::getTitle() const {
//    return title;
//}

//QDateTime Event::getDateTime() const {
//    return dateTime;
//}

//QString Event::getCategory() const {
//    return category;
//}


// event.cpp
//#include "event.h"

//Event::Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description)
//    : title(title), dateTime(dateTime), category(category), description(description) {}

//QString Event::getTitle() const { return title; }
//QDateTime Event::getDateTime() const { return dateTime; }
//QString Event::getCategory() const { return category; }
//QString Event::getDescription() const { return description; }

/*=================================================*/

#include "event.h"

// 构造函数的定义
Event::Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description)
    : title(title), dateTime(dateTime), category(category), description(description) {}

// 方法定义
QString Event::getTitle() const { return title; }
QDateTime Event::getDateTime() const { return dateTime; }
QString Event::getCategory() const { return category; }
QString Event::getDescription() const { return description; }

// setter 方法实现
void Event::setTitle(const QString &title) { this->title = title; }
void Event::setDateTime(const QDateTime &dateTime) { this->dateTime = dateTime; }
void Event::setCategory(const QString &category) { this->category = category; }
void Event::setDescription(const QString &description) { this->description = description; }
void Event::setRemindTime(const QTime &remindTime) { this->remindTime = remindTime; } // 如果需要

