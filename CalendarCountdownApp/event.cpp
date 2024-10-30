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
#include "event.h"

Event::Event(const QString &title, const QDateTime &dateTime, const QString &category, const QString &description)
    : title(title), dateTime(dateTime), category(category), description(description) {}

QString Event::getTitle() const { return title; }
QDateTime Event::getDateTime() const { return dateTime; }
QString Event::getCategory() const { return category; }
QString Event::getDescription() const { return description; }

