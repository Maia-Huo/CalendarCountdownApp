// utils/notifier.cpp
#include "notifier.h"
#include <QTimer>
#include <QDebug>

Notifier::Notifier(QObject *parent)
    : QObject(parent), db("database/calendar.db")
{
    db.initialize();
    moveToThread(&workerThread);
    connect(&workerThread, &QThread::started, this, &Notifier::process);
    connect(this, &Notifier::notify, [](const QString &title, const QString &message){
        // 使用QSystemTrayIcon发送通知
        // 此处假设主窗口已经创建并设置了QSystemTrayIcon
    });
    workerThread.start();
}

Notifier::~Notifier()
{
    workerThread.quit();
    workerThread.wait();
}

void Notifier::start()
{
    // 可以添加初始化代码
}

void Notifier::process()
{
    while (true)
    {
        QDateTime current = QDateTime::currentDateTime();
        QList<Event> events = db.getAllEvents();
        for (const auto &event : events)
        {
            QDateTime eventDateTime = QDateTime::fromString(event.date + " " + event.time, "yyyy-MM-dd HH:mm");
            QDateTime remindDateTime = eventDateTime.addSecs(-/*转换remindTime为秒*/);
            // 假设remindTime是提前分钟数
            int remindMinutes = 10; // 默认提前10分钟
            if (!event.remindTime.isEmpty())
                remindMinutes = event.remindTime.toInt();
            remindDateTime = eventDateTime.addSecs(-remindMinutes * 60);

            if (current >= remindDateTime && current < remindDateTime.addSecs(60))
            {
                emit notify("事件提醒", QString("即将发生的事件: %1").arg(event.title));
            }
        }
        QThread::sleep(60); // 每分钟检查一次
    }
}
