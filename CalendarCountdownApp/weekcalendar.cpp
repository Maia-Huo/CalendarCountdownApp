#include "weekcalendar.h"
#include "ui_weekcalendar.h"
#include <QDate>
#include <QDebug>
#include <QTextCharFormat>

WeekCalendar::WeekCalendar(QWidget *parent) :
    QWidget(parent), ui(new Ui::WeekCalendar), storage(new SQLiteStorage()) {
    ui->setupUi(this);
    initializeCalendar();  // 初始化日历，设置为当前周

    connect(ui->lastWeekButton, &QPushButton::clicked, this, &WeekCalendar::on_lastWeekButton_clicked);
    connect(ui->weekButton, &QPushButton::clicked, this, &WeekCalendar::on_nowWeekButton_clicked);
    connect(ui->nextWeekButton, &QPushButton::clicked, this, &WeekCalendar::on_nextWeekButton_clicked);
}

WeekCalendar::~WeekCalendar() {
    delete ui;
}

void WeekCalendar::initializeCalendar() {
    // 获取当前日期
    QDate currentDate = QDate::currentDate();

    // 设置 QCalendarWidget 显示当前周
    ui->calendarWidget->setSelectedDate(currentDate);  // 选中当前日期
    ui->calendarWidget->setFirstDayOfWeek(Qt::Monday); // 设置星期天为一周的开始

    // 计算当前周的开始和结束日期
    int daysToStartOfWeek = currentDate.dayOfWeek() -1;
    startOfWeek = currentDate.addDays(-daysToStartOfWeek);
    endOfWeek = startOfWeek.addDays(6);

    updateCalendarDisplay(startOfWeek,endOfWeek); //更新窗口
}

//获取筛选后的事件文本列表
QList<QString> WeekCalendar::selectDataEvents(const QDate &selectedDate) {
    //selectedEvents.clear();  // 清空之前的筛选结果

    QList<QString> selectedEvents;  // 用于存储筛选后的事件文本
    QVector<Event> AllEvents = storage->getAllEvents(); // 从数据库读取所有事件

    for (const Event &event : AllEvents) {
        if (event.getDateTime().date() == selectedDate) { // 仅显示选中日期的事件

            QString displayText = QString("%1 - %2 (%3)")
                .arg(event.getTitle())
                .arg(event.getDateTime().toString("hh:mm"))
                .arg(event.getCategory());

            selectedEvents.append(displayText); //添加到列表
        }
    }

    return selectedEvents;
}

//显示当前事件文本列表
void WeekCalendar::displaySelectEvents(int number,const QDate &selectedDate) {
    // 调用 selectDataEvents 函数获取筛选后的事件文本
    QList<QString> selectedEvents = selectDataEvents(selectedDate);
    // 动态获取 QTextBrowser 控件
    QTextBrowser* textBrowser = findChild<QTextBrowser*>(QString("textEvents_%1").arg(number + 1));

    textBrowser->clear();// 清空 QTextBrowser 内容

    // 获取事件文本的数量
    int eventCount = selectedEvents.size();

    if(eventCount > 0 && textBrowser) {
        for(int i = 0;i < eventCount;i++) {
            QString displayText = selectedEvents[i]; // 从 selectedEvents 列表中获取第 i 个事件的文本
            textBrowser->setPlainText(displayText);  // 设置事件文本
        }
    }
}

void WeekCalendar::on_lastWeekButton_clicked() {
    QDate today = QDate::currentDate();
    int daysToMonday = today.dayOfWeek() - 1;  // 计算距离周一的天数
    QDate currentWeekStart = today.addDays(-daysToMonday);

    // 计算上一周的开始和结束日期
    QDate lastWeekStart = currentWeekStart.addDays(-7);  // 上一周的开始日期
    QDate lastWeekEnd = lastWeekStart.addDays(6);        // 上一周的结束日期

    // 更新日历显示
    updateCalendarDisplay(lastWeekStart, lastWeekEnd);

    // 更新类成员的开始和结束日期
    startOfWeek = lastWeekStart;
    endOfWeek = lastWeekEnd;

    // 让 calendarWidget 跳转到新的周开始日期
    ui->calendarWidget->setSelectedDate(startOfWeek);
    ui->calendarWidget->setFocus();  // 聚焦到新的日期
}

void WeekCalendar::on_nowWeekButton_clicked() {
    QDate today = QDate::currentDate();

    // 计算当前周的开始和结束日期
    int daysToStartOfWeek = today.dayOfWeek() -1;
    startOfWeek = today.addDays(-daysToStartOfWeek);
    endOfWeek = startOfWeek.addDays(6);

    // 更新日历显示
    updateCalendarDisplay(startOfWeek, endOfWeek);

    // 让 calendarWidget 跳转到新的周开始日期
    ui->calendarWidget->setSelectedDate(startOfWeek);
    ui->calendarWidget->setFocus();
}

void WeekCalendar::on_nextWeekButton_clicked() {
    QDate today = QDate::currentDate();
    int daysToMonday = today.dayOfWeek() - 1;  // 计算距离周一的天数
    QDate currentWeekStart = today.addDays(-daysToMonday);

    // 计算下一周的开始和结束日期
    startOfWeek = currentWeekStart.addDays(+7);  // 下一周的开始日期
    endOfWeek = startOfWeek.addDays(6);  // 下一周的结束日期

    // 更新日历显示
    updateCalendarDisplay(startOfWeek, endOfWeek);

    // 让 calendarWidget 跳转到新的周开始日期
    ui->calendarWidget->setSelectedDate(startOfWeek);
    ui->calendarWidget->setFocus();
}

void WeekCalendar::updateCalendarDisplay(const QDate &startOfWeek, const QDate &endOfWeek) {
    // 重置日历格式
    QTextCharFormat defaultFormat;
    ui->calendarWidget->setDateTextFormat(ui->calendarWidget->minimumDate(), defaultFormat);

    // 高亮当前周日期
    QTextCharFormat highlightFormat;// 创建高亮格式
    highlightFormat.setBackground(Qt::yellow);// 设置当前周日期背景颜色
    highlightFormat.setForeground(Qt::black);
    // 高亮当前周的日期
    for (QDate date = startOfWeek; date <= endOfWeek; date = date.addDays(1)) {
        ui->calendarWidget->setDateTextFormat(date, highlightFormat);
    }

    // 设置非当前周日期为灰色
    QTextCharFormat outOfWeekFormat;
    outOfWeekFormat.setForeground(Qt::lightGray);
    for (QDate date = ui->calendarWidget->minimumDate(); date <= ui->calendarWidget->maximumDate(); date = date.addDays(1)) {
        if (date < startOfWeek || date > endOfWeek) {
            ui->calendarWidget->setDateTextFormat(date, outOfWeekFormat);
        }
    }

    // 禁用导航栏，避免跳转到其他月份
    //ui->calendarWidget->setNavigationBarVisible(false);

    // 更新每个日期标签
    for (int i = 0; i < 7; ++i) {
        QDate day = startOfWeek.addDays(i);
        QString dateText = day.toString("yyyy-MM-dd");

        switch (i) {
            case 0: ui->date_1->setText(dateText); displaySelectEvents(i, day); break;
            case 1: ui->date_2->setText(dateText); displaySelectEvents(i, day); break;
            case 2: ui->date_3->setText(dateText); displaySelectEvents(i, day); break;
            case 3: ui->date_4->setText(dateText); displaySelectEvents(i, day); break;
            case 4: ui->date_5->setText(dateText); displaySelectEvents(i, day); break;
            case 5: ui->date_6->setText(dateText); displaySelectEvents(i, day); break;
            case 6: ui->date_7->setText(dateText); displaySelectEvents(i, day); break;
        }
    }
}


void WeekCalendar::on_closeButton_clicked() {
    this->close(); // 关闭周视图窗口

    // 显示主窗口
    if (parentWidget()) {
        parentWidget()->show(); // 显示主窗口
    }
}
