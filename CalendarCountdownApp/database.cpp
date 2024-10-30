#include "database.h"

void Database::addEvent(const Event &event) {
    events.append(event);
}

QList<Event> Database::getEvents() const {
    return events;
}


/*=================================================*/
