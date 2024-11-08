#include "showevents.h"
#include "ui_showevents.h"
#include "sqlitestorage.h"
#include <QStringList>

ShowEvents::ShowEvents(QWidget *parent)
    : QWidget(parent), ui(new Ui::ShowEvents), storage(new SQLiteStorage()){
    ui->setupUi(this);  // 加载 UI 布局
    initShowEvents();  // 设置每个月的日历视图
}

ShowEvents::~ShowEvents() {
    delete ui;
}

void ShowEvents::initShowEvents(){
    // 清空当前事件列表
    ui->listWidget->clear();

    // 从数据库获取所有事件
    QVector<Event> AllEvents = storage->getAllEvents(); // 从数据库读取事件

    for (const Event &event : AllEvents) {
        QString displayText = QString("%1 %2 - %3 (%4)")
            .arg(event.getDateTime().date().toString("yyyy-MM-dd"))
            .arg(event.getTitle())
            .arg(event.getDateTime().toString("hh:mm"))
            .arg(event.getCategory());
        ui->listWidget->addItem(displayText);
    }
}
