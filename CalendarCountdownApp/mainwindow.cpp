#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db("database/calendar.db")
{
    ui->setupUi(this);
    db.initialize();

    //点击事件
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::on_calendarDataClicked);
    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::on_addEventButton_clicked);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
    countdownTimer->start(1000);

    QDate today = QDate::currentDate();
    ui->calendarWidget->setSelectedDate(today);
    updateEventList(today);

    notifier.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarDateClicked(const QDate &date)
{
    updateEventList(date);
}

void MainWindow::on_addEventButton_clicked()
{
    EventDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Event event = dialog.getEvent();
        db.addEvent(event);
        updateEventList(event.date);
        notifier.checkAndNotify(); // 检查是否需要提醒
    }
}

void MainWindow::updateEventList(const QDate &date)
{
    ui->eventListWidget->clear();
    QList<Event> events = db.getEventsByDate(date.toString("yyyy-MM-dd"));
    for (const auto &event : events)
    {
        QString itemText = QString("%1 %2").arg(event.time, event.title);
        QListWidgetItem *item = new QListWidgetItem(itemText, ui->eventListWidget);
        item->setData(Qt::UserRole, event.id);
    }
}

void MainWindow::updateCountdown()
{
    Event nextEvent = db.getNextEvent();
    if (nextEvent.id != -1)
    {
        QDateTime eventDateTime = QDateTime::fromString(nextEvent.date + " " + nextEvent.time, "yyyy-MM-dd HH:mm");
        QDateTime currentDateTime = QDateTime::currentDateTime();
        qint64 seconds = currentDateTime.secsTo(eventDateTime);
        if (seconds > 0)
        {
            int days = seconds / 86400;
            seconds %= 86400;
            int hours = seconds / 3600;
            seconds %= 3600;
            int minutes = seconds / 60;
            int secs = seconds % 60;
            QString countdown = QString("下一个事件: %1\n还有 %2 天 %3 小时 %4 分钟 %5 秒")
                                    .arg(nextEvent.title)
                                    .arg(days)
                                    .arg(hours)
                                    .arg(minutes)
                                    .arg(secs);
            ui->countdownLabel->setText(countdown);
        }
        else
        {
            ui->countdownLabel->setText("事件已过期");
        }
    }
    else
    {
        ui->countdownLabel->setText("没有即将到来的事件");
    }
}
