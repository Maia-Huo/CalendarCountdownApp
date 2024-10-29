// models/event.h
#ifndef EVENT_H
#define EVENT_H

#include <QString>

struct Event
{
    int id;
    QString title;
    QString date; // 格式: "yyyy-MM-dd"
    QString time; // 格式: "HH:mm"
    QString category;
    QString remindTime; // 提醒时间, 可以存储为"yyyy-MM-dd HH:mm"或提前的分钟数
    QString description;

    Event()
        : id(-1) {}
};

#endif // EVENT_H
