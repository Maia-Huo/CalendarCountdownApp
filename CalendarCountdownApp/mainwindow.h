
//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include <QMainWindow>
//#include <QCalendarWidget>
//#include <QList>
//#include "event.h"
//#include <QListWidgetItem>
//#include <QSet>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow {
//    Q_OBJECT

//public:
//    explicit MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();


//private slots:
//    void addEvent();  // 添加事件
//    void updateEventList();  // 更新事件列表
//    void showSelectedDateEvents(const QDate &date);  // 显示选择日期的事件
//    void checkUpcomingEvents();  // 检查即将发生的事件
//    void showCountdown();  // 显示倒计时
//    void editEvent(QListWidgetItem *item);
//    void deleteEvent();

//private:
//    Ui::MainWindow *ui;
//    QCalendarWidget *calendarWidget;
//    QList<Event> events;  // 存储事件的列表
//    QSet<QString> notifiedEvents; // 存储已提醒的事件标题
//};

//#endif // MAINWINDOW_H


/*=================================================*/


/*22222222222222222222222222222222222222222222222222*/



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QList>
#include "event.h"
#include <QListWidgetItem>
#include <QSet>
#include "countdownwindow.h"
#include "sqlitestorage.h"
#include "yearcalendar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void addEvent();                                 // 添加事件
    void updateEventList();                          // 更新事件列表
    void showSelectedDateEvents(const QDate &date);  // 显示选择日期的事件
    void checkUpcomingEvents();                      // 检查即将发生的事件
    void showCountdown();                            // 显示倒计时
    void editEvent(QListWidgetItem *item);
    void deleteEvent();

    void showYear();//年视图
    void showWeek();//周视图

private:
    Ui::MainWindow *ui;
    QCalendarWidget *calendarWidget;
    QList<Event> events;          // 选中日期的事件的列表
    QList<Event> allEvents;          // 从数据库获取的所有事件
    QSet<QString> notifiedEvents; // 存储已提醒的事件标题

    QDate selectedDate;

    //YearCalendar *yearCalendarWindow;  // 声明 yearCalendarWindow 指针
    SQLiteStorage *storage; // 数据库存储类
};

#endif // MAINWINDOW_H
