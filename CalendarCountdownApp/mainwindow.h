#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countdownwindow.h"
#include "weatherfetcher.h"
#include "sqlitestorage.h"
#include "yearcalendar.h"
#include "showevents.h"
#include "event.h"
#include <QSet>
#include <QList>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QCalendarWidget>
#include <QListWidgetItem>

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
    void showEvents();//显示所有事件

    void onWeatherButtonClicked();  // 按钮点击获取天气信息
    void updateWeatherDisplay(const QString &weather, double temp, const QString &location);

private:
    Ui::MainWindow *ui;
    QCalendarWidget *calendarWidget;
    QList<Event> events;          // 选中日期的事件的列表
    QList<Event> allEvents;          // 从数据库获取的所有事件
    QSet<QString> notifiedEvents; // 存储已提醒的事件标题

    QDate selectedDate;

    //YearCalendar *yearCalendarWindow;  // 声明 yearCalendarWindow 指针
    SQLiteStorage *storage; // 数据库存储类

    WeatherFetcher *weatherFetcher;  // 用于获取天气数据的对象
};

#endif // MAINWINDOW_H
