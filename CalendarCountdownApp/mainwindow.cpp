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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QDateTime>
#include "eventdialog.h"
#include "notifier.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::addEvent);
    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::showSelectedDateEvents);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
    timer->start(60000); // 每分钟检查一次
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
    ui->eventListWidget->clear();
    for (const Event &event : events) {
        ui->eventListWidget->addItem(event.getTitle());
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


/*=================================================*/
