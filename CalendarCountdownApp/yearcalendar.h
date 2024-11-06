#ifndef YEARCALENDAR_H
#define YEARCALENDAR_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>

namespace Ui {
class YearCalendar;
}

class YearCalendar : public QWidget {
    Q_OBJECT

public:
    explicit YearCalendar(int year = QDate::currentDate().year(), QWidget *parent = nullptr);
    ~YearCalendar();

private slots:
    void on_closeButton_clicked();  // 关闭按钮的槽函数

private:
    Ui::YearCalendar *ui;
    void initializeCalendars(int year);  // 初始化各个月的日历视图
};

#endif // YEARCALENDAR_H
