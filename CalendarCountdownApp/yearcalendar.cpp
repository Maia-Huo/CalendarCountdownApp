#include "yearcalendar.h"
#include "ui_yearcalendar.h"  // 自动生成的 UI 头文件

YearCalendar::YearCalendar(int year, QWidget *parent)
    : QWidget(parent), ui(new Ui::YearCalendar) {
    ui->setupUi(this);  // 加载 UI 布局
    initializeCalendars(year);  // 设置每个月的日历视图
}

YearCalendar::~YearCalendar() {
    delete ui;
}

void YearCalendar::initializeCalendars(int year) {
    // 设置 12 个日历控件，分别对应 1 到 12 月
    QCalendarWidget *calendars[12] = {
        ui->calendarJanuary, ui->calendarFebruary, ui->calendarMarch, ui->calendarApril,
        ui->calendarMay, ui->calendarJune, ui->calendarJuly, ui->calendarAugust,
        ui->calendarSeptember, ui->calendarOctober, ui->calendarNovember, ui->calendarDecember
    };

    for (int month = 1; month <= 12; ++month) {
        QCalendarWidget *calendar = calendars[month - 1];
        calendar->setCurrentPage(year, month);   // 设置年份和月份
        calendar->setGridVisible(true);          // 显示网格线
        calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);  // 隐藏周号
        //calendar->setNavigationBarVisible(false); // 禁用导航栏
    }
}

void YearCalendar::on_closeButton_clicked() {
    this->close(); // 关闭年视图窗口

    // 显示主窗口
    if (parentWidget()) {
        parentWidget()->show(); // 显示主窗口
    }
}
