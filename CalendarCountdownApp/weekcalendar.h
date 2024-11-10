#ifndef WEEKCALENDAR_H
#define WEEKCALENDAR_H

#include "ui_weekcalendar.h"
#include "sqlitestorage.h"
#include <QDate>
#include <QDebug>
#include <QWidget>
#include <QWidget>
#include <QListView>
#include <QCalendarWidget>
#include <QStringListModel>


namespace Ui {
class WeekCalendar;
}

class WeekCalendar : public QWidget {
    Q_OBJECT

public:
    explicit WeekCalendar(QWidget *parent = nullptr);
    ~WeekCalendar();

private slots:
    void on_lastWeekButton_clicked(); //计算上一周并显示
    void on_nowWeekButton_clicked();//计算本周并显示
    void on_nextWeekButton_clicked(); //计算下一周并显示
    void on_closeButton_clicked();  // 关闭按钮的槽函数

private:
    Ui::WeekCalendar *ui;
    SQLiteStorage *storage; // 数据库存储类
    QList<QString> selectedEvents;  // 用于存储筛选后的事件
    QDate startOfWeek; //记录当前周的开始日期，每次切换周查看时间，根据该日期进行调整
    QDate endOfWeek;
    void initializeCalendar();  // 初始化日历，只显示当前周
    QList<QString> selectDataEvents(const QDate &date);
    void displaySelectEvents(int days, const QDate &selectedDate);
    void updateCalendarDisplay(const QDate &startOfWeek, const QDate &endOfWeek);//更新窗口
};

#endif // WEEKCALENDAR_H
