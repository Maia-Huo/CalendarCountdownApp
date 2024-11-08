#ifndef DATABASE_H
#define DATABASE_H

#include "event.h"
#include <QList>
#include <QString>

class Database {
public:
    void addEvent(const Event &event);
    QList<Event> getEvents() const;

private:
    QList<Event> events; // 存储事件列表
};

#endif // DATABASE_H
