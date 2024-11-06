#ifndef WEEKCALENDAR_H
#define WEEKCALENDAR_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include "ui_weekcalendar.h"

namespace Ui {
class WeekCalendar;
}

class WeekCalendar : public QWidget {
    Q_OBJECT

public:
    explicit WeekCalendar(QWidget *parent = nullptr);
    ~WeekCalendar();

private slots:
    void on_closeButton_clicked();  // 关闭按钮的槽函数

private:
    Ui::WeekCalendar *ui;
    void initializeCalendar();  // 初始化日历，只显示当前周
};

#endif // WEEKCALENDAR_H
