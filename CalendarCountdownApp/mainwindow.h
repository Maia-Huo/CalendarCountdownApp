//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include <QMainWindow>
//#include <QCalendarWidget>
//#include <QTabWidget>
//#include <QList>
//#include "event.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow {
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//private slots:
//    void checkUpcomingEvents();

//private:
//    Ui::MainWindow *ui;
//    QTabWidget *tabWidget;
//    QCalendarWidget *calendarWidget;
//    QList<Event> events; // 存储事件列表

//    void setupCalendar();
//    void showCountdown();
//};

//#endif // MAINWINDOW_H


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QList>
#include "event.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addEvent();  // 添加事件
    void updateEventList();  // 更新事件列表
    void showSelectedDateEvents(const QDate &date);  // 显示选择日期的事件
    void checkUpcomingEvents();  // 检查即将发生的事件
    void showCountdown();  // 显示倒计时

private:
    Ui::MainWindow *ui;
    QCalendarWidget *calendarWidget;
    QList<Event> events;  // 存储事件的列表
};

#endif // MAINWINDOW_H
