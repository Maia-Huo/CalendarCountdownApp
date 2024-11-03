#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>
#include "event.h"

class Database {
public:
    void addEvent(const Event &event);
    QList<Event> getEvents() const;

private:
    QList<Event> events; // 存储事件列表
};

#endif // DATABASE_H


/*=================================================*/

/*22222222222222222222222222222222222222222222222222*/
