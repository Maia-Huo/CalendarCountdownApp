#include "weekcalendar.h"
#include "ui_weekcalendar.h"
#include <QTextCharFormat>

WeekCalendar::WeekCalendar(QWidget *parent) :
    QWidget(parent), ui(new Ui::WeekCalendar) {
    ui->setupUi(this);
    initializeCalendar();  // 初始化日历，设置为当前周
}

WeekCalendar::~WeekCalendar() {
    delete ui;
}

void WeekCalendar::initializeCalendar() {
    // 获取当前日期
    QDate currentDate = QDate::currentDate();

    // 设置 QCalendarWidget 显示当前周
    ui->calendarWidget->setSelectedDate(currentDate);  // 选中当前日期
    ui->calendarWidget->setFirstDayOfWeek(Qt::Sunday); // 设置星期天为一周的开始

    // 计算当前周的开始和结束日期
    int daysToStartOfWeek = currentDate.dayOfWeek() - 1;
    QDate startOfWeek = currentDate.addDays(-daysToStartOfWeek);
    QDate endOfWeek = startOfWeek.addDays(6);

    // 创建高亮格式
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow);  // 设置当前周日期背景颜色
    highlightFormat.setForeground(Qt::black);

    // 高亮当前周的日期
    for (QDate date = startOfWeek; date <= endOfWeek; date = date.addDays(1)) {
        ui->calendarWidget->setDateTextFormat(date, highlightFormat);
    }

    // 设置非当前周的日期为灰色
    QTextCharFormat outOfWeekFormat;
    outOfWeekFormat.setForeground(Qt::lightGray);
    for (QDate date = ui->calendarWidget->minimumDate(); date <= ui->calendarWidget->maximumDate(); date = date.addDays(1)) {
        if (date < startOfWeek || date > endOfWeek) {
            ui->calendarWidget->setDateTextFormat(date, outOfWeekFormat);
        }
    }

    // 禁用导航栏，避免跳转到其他月份
    //ui->calendarWidget->setNavigationBarVisible(false);
}

void WeekCalendar::on_closeButton_clicked() {
    this->close(); // 关闭周视图窗口

    // 显示主窗口
    if (parentWidget()) {
        parentWidget()->show(); // 显示主窗口
    }
}
