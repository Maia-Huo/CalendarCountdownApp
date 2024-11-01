//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QTimer>
//#include <QMessageBox>
//#include <QDateTime>
//#include "eventdialog.h"   // 添加这一行
//#include "notifier.h"      // 添加这一行

//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent), ui(new Ui::MainWindow) {
//    ui->setupUi(this);

//    tabWidget = new QTabWidget(this);
//    calendarWidget = new QCalendarWidget(this);
//    tabWidget->addTab(calendarWidget, "月视图");
//    setCentralWidget(tabWidget);

//    setupCalendar();

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
//    timer->start(60000); // 每分钟检查一次
//}

//MainWindow::~MainWindow() {
//    delete ui;
//}

//void MainWindow::setupCalendar() {
//    connect(calendarWidget, &QCalendarWidget::clicked, this, [=](const QDate &date) {
//        EventDialog dialog(this);
//        if (dialog.exec() == QDialog::Accepted) {
//            Event newEvent = dialog.getEvent();
//            events.append(newEvent);
//            // 在日历中显示事件的逻辑
//        }
//    });
//}

//void MainWindow::checkUpcomingEvents() {
//    for (const Event &event : events) {
//        if (event.getDateTime() < QDateTime::currentDateTime().addSecs(60)) { // 修改为 addSecs(60)
//            Notifier::showNotification(event.getTitle() + "即将到来!"); // 修正字符串
//        }
//    }
//}

//void MainWindow::showCountdown() {
//    if (events.isEmpty()) return;

//    Event upcomingEvent = events.first(); // 取第一个事件
//    // 实现倒计时显示的逻辑
//}


//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QTimer>
//#include <QMessageBox>
//#include <QDateTime>
//#include "eventdialog.h"
//#include "notifier.h"

//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent), ui(new Ui::MainWindow) {
//    ui->setupUi(this);

//    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::addEvent);
//    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::showSelectedDateEvents);

//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
//    timer->start(60000); // 每分钟检查一次
//}

//MainWindow::~MainWindow() {
//    delete ui;
//}

//void MainWindow::addEvent() {
//    EventDialog dialog(this);
//    if (dialog.exec() == QDialog::Accepted) {
//        Event newEvent = dialog.getEvent();
//        events.append(newEvent);
//        updateEventList();
//        // 在日历中显示事件
//        // 你需要实现相应的逻辑以在日历上标记事件
//    }
//}

//void MainWindow::updateEventList() {
//    ui->eventListWidget->clear();
//    for (const Event &event : events) {
//        ui->eventListWidget->addItem(event.getTitle());
//    }
//}

//void MainWindow::showSelectedDateEvents(const QDate &date) {
//    ui->eventListWidget->clear();
//    for (const Event &event : events) {
//        if (event.getDateTime().date() == date) {
//            ui->eventListWidget->addItem(event.getTitle());
//        }
//    }
//}

//void MainWindow::checkUpcomingEvents() {
//    for (const Event &event : events) {
//        if (event.getDateTime() < QDateTime::currentDateTime().addSecs(60)) {
//            Notifier::showNotification(event.getTitle() + "即将到来!");
//        }
//    }
//}

//void MainWindow::showCountdown() {
//    if (events.isEmpty()) return;

//    Event upcomingEvent = events.first(); // 取第一个事件
//    // 实现倒计时显示的逻辑
//}


/*=================================================*/



/*22222222222222222222222222222222222222222222222222*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QDateTime>
#include "eventdialog.h"
#include "notifier.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::addEvent);
    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::showSelectedDateEvents);
    connect(ui->eventListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::editEvent);
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &MainWindow::deleteEvent);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
    timer->start(60000); // 每分钟检查一次

    // 新增的定时器，每秒更新倒计时
    QTimer *countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateEventList);
    countdownTimer->start(1000); // 每秒更新一次
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addEvent() {
    EventDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Event newEvent = dialog.getEvent();
        events.append(newEvent);
        updateEventList();
        // 在日历中显示事件
        // 你需要实现相应的逻辑以在日历上标记事件
    }
}



void MainWindow::updateEventList() {
    // 保存当前选中的事件的索引
    int currentIndex = ui->eventListWidget->currentRow();

    ui->eventListWidget->clear();
    for (const Event &event : events) {
        QString displayText = QString("%1 - %2 (%3)")
            .arg(event.getTitle())
            .arg(event.getDateTime().toString("yyyy-MM-dd hh:mm"))
            .arg(event.getCategory());

        // 计算倒计时
        qint64 secondsToEvent = QDateTime::currentDateTime().secsTo(event.getDateTime());
        if (secondsToEvent > 0) {
            QString countdownText = QString("倒计时: %1").arg(QTime(0, 0).addSecs(secondsToEvent).toString("HH:mm:ss"));
            displayText += " " + countdownText;
        } else {
            displayText += " (已过期)";
        }

        ui->eventListWidget->addItem(displayText);
    }

    // 如果之前有选中的项，重新设置选中状态
    if (currentIndex >= 0 && currentIndex < ui->eventListWidget->count()) {
        ui->eventListWidget->setCurrentRow(currentIndex);
    }
}








void MainWindow::showSelectedDateEvents(const QDate &date) {
    ui->eventListWidget->clear();
    for (const Event &event : events) {
        if (event.getDateTime().date() == date) {
            ui->eventListWidget->addItem(event.getTitle());
        }
    }
}

void MainWindow::checkUpcomingEvents() {
    for (const Event &event : events) {
        if (event.getDateTime() < QDateTime::currentDateTime().addSecs(60)) {
            Notifier::showNotification(event.getTitle() + "即将到来!");
        }
    }
}

void MainWindow::showCountdown() {
    if (events.isEmpty()) return;

    Event upcomingEvent = events.first(); // 取第一个事件
    // 实现倒计时显示的逻辑
}

void MainWindow::editEvent(QListWidgetItem *item) {
    int index = ui->eventListWidget->row(item);
    if (index < 0 || index >= events.size()) return;

    EventDialog dialog(this);
    // 设置 dialog 的初始值
    const Event &event = events[index];
    dialog.setTitle(event.getTitle());
    dialog.setDateTime(event.getDateTime());
    dialog.setCategory(event.getCategory());
    dialog.setDescription(event.getDescription());
    dialog.setRemindTime(event.getRemindTime());

    if (dialog.exec() == QDialog::Accepted) {
        events[index] = dialog.getEvent(); // 更新事件
        updateEventList(); // 刷新事件列表
    }
}



void MainWindow::deleteEvent() {
    QListWidgetItem *currentItem = ui->eventListWidget->currentItem();
    if (currentItem) {
        QString title = currentItem->text().trimmed();
        qDebug() << "Attempting to delete event:" << title;

        auto it = std::remove_if(events.begin(), events.end(), [&](const Event &event) {
            return event.getTitle() == title.split(" - ").first(); // 直接比较标题，匹配时只用事件标题部分
        });

        if (it != events.end()) {
            events.erase(it, events.end());
            qDebug() << "Event deleted:" << title;
            updateEventList();
        } else {
            qDebug() << "Event not found:" << title;
        }
    } else {
        QMessageBox::warning(this, "删除事件", "请选择要删除的事件。");
    }
}
