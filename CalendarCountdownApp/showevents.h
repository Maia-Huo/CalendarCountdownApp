#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include "sqlitestorage.h"
#include <QWidget>
#include <QListView>
#include <QStringListModel>

namespace Ui {
class ShowEvents;
}

class ShowEvents : public QWidget {
    Q_OBJECT

public:
    explicit ShowEvents(QWidget *parent = nullptr);
    ~ShowEvents();

private:
    Ui::ShowEvents *ui;
    SQLiteStorage *storage; // 数据库存储类
    void initShowEvents();  // 初始化日历
};

#endif // EVENTWINDOW_H
