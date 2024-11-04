
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QDateTime>
#include "eventdialog.h"
#include "notifier.h"
#include <QDebug>
#include <QSet>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::addEvent);
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::showSelectedDateEvents);

    connect(ui->eventListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::editEvent);
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &MainWindow::deleteEvent);

    connect(ui->showCountdownButton, &QPushButton::clicked, this, &MainWindow::showCountdown);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
    timer->start(1000);

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
    QDate selectedDate = ui->calendarWidget->selectedDate();
    dialog.setSelectedDate(selectedDate);  // 设置默认日期为选中日期

    if (dialog.exec() == QDialog::Accepted) {
        Event newEvent = dialog.getEvent();
        events.append(newEvent);
        showSelectedDateEvents(selectedDate);  // 更新事件列表，仅显示当前选中日期的事件
    }
}



void MainWindow::updateEventList() {
    // 保存当前选中的事件的索引
    int currentIndex = ui->eventListWidget->currentRow();

    ui->eventListWidget->clear();
    for (const Event &event : events) {
        if (event.getDateTime().date() == selectedDate) { // 仅显示选中日期的事件
            QString displayText = QString("%1 - %2 (%3)")
                .arg(event.getTitle())
                .arg(event.getDateTime().toString("hh:mm"))
                .arg(event.getCategory());

            // 计算倒计时
            qint64 secondsToEvent = QDateTime::currentDateTime().secsTo(event.getDateTime());
            if (secondsToEvent > 0) {
                int hours = secondsToEvent / 3600;
                int minutes = (secondsToEvent % 3600) / 60;
                int seconds = secondsToEvent % 60;

                QString countdownText = QString("倒计时: %1小时 %2分钟 %3秒")
                    .arg(hours)
                    .arg(minutes)
                    .arg(seconds);
                displayText += " " + countdownText;
            } else {
                displayText += " (已过期)";
            }

            ui->eventListWidget->addItem(displayText);
        }
    }

    // 如果之前有选中的项，重新设置选中状态
    if (currentIndex >= 0 && currentIndex < ui->eventListWidget->count()) {
        ui->eventListWidget->setCurrentRow(currentIndex);
    }
}



void MainWindow::showSelectedDateEvents(const QDate &date) {
    selectedDate = date; // 更新当前选中的日期
    updateEventList(); // 更新事件列表
}




void MainWindow::checkUpcomingEvents() {
    for (auto it = events.begin(); it != events.end();) {
        if (it->getDateTime() < QDateTime::currentDateTime().addSecs(60)) {
            QString title = it->getTitle();
            if (!notifiedEvents.contains(title)) {
                Notifier::showNotification(title + "即将到来!");
                notifiedEvents.insert(title); // 标记为已提醒
                it = events.erase(it); // 删除事件
            } else {
                ++it; // 如果已经提醒过，继续下一个事件
            }
        } else {
            ++it; // 继续下一个事件
        }
    }
    updateEventList(); // 更新事件列表
}



void MainWindow::showCountdown() {
    if (events.isEmpty()) return;

    // 找到最近的事件
    Event closestEvent = events.first();
    for (const Event &event : events) {
        if (event.getDateTime() < closestEvent.getDateTime() &&
            event.getDateTime() > QDateTime::currentDateTime()) {
            closestEvent = event;
        }
    }

    CountdownWindow *countdownWindow = new CountdownWindow(this);
    countdownWindow->startCountdown(closestEvent.getDateTime());
    countdownWindow->show();

    this->hide(); // 隐藏主窗口
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


