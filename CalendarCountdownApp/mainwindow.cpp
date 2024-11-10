#include "mainwindow.h"
#include "notifier.h"
#include "eventdialog.h"
#include "ui_mainwindow.h"
#include "sqlitestorage.h"
#include "yearcalendar.h"
#include "weekcalendar.h"
#include "weatherfetcher.h"
#include "showevents.h"
#include <QSet>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), storage(new SQLiteStorage()),
      weatherFetcher(new WeatherFetcher()){
    ui->setupUi(this);

    // 连接按钮点击信号到槽函数 onWeatherButtonClicked
    connect(ui->weatherButton, &QPushButton::clicked, this, &MainWindow::onWeatherButtonClicked);
    // 连接 WeatherFetcher 的 weatherFetched 信号到槽函数 updateWeatherDisplay
    connect(weatherFetcher, &WeatherFetcher::weatherFetched, this, &MainWindow::updateWeatherDisplay);

    //将showYear函数连接到按钮
    connect(ui->yearViewButton, &QPushButton::clicked, this, &MainWindow::showYear);

    //将showWeek函数连接到按钮
    connect(ui->weekViewButton, &QPushButton::clicked, this, &MainWindow::showWeek);

    //将showEvents函数连接到按钮
    connect(ui->searchAction, &QAction::triggered, this, &MainWindow::showEvents);

    connect(ui->addEventButton, &QPushButton::clicked, this, &MainWindow::addEvent);
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &MainWindow::deleteEvent);

    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::showSelectedDateEvents);
    connect(ui->eventListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::editEvent);

    connect(ui->showCountdownButton, &QPushButton::clicked, this, &MainWindow::showCountdown);
    //初始日程显示
    QDate currentDate = QDate::currentDate();// 获取当前日期
    showSelectedDateEvents(currentDate);// 自动选中当前日期并更新事件列表

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkUpcomingEvents);
    timer->start(1000);

    // 新增的定时器，每秒更新倒计时
    QTimer *countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateEventList);
    countdownTimer->start(3000); // 每秒更新一次
}

MainWindow::~MainWindow() {
    delete ui;
    //delete storage; // 在析构函数中删除实例
}


//天气
// 按钮点击槽函数，用于发起天气数据请求
void MainWindow::onWeatherButtonClicked() {
    // 清空之前显示的内容
    ui->weatherLabel->clear();
    ui->tempLabel->clear();
    // 获取用户选择的城市
    QString city = ui->comboBox->currentText().trimmed();  // 从下拉菜单中获取城市名称

    if(city == "北京"){
        weatherFetcher->fetchWeather("Beijing");
    }else if(city == "上海"){
        weatherFetcher->fetchWeather("Shanghai");
    }else if(city == "广州"){
        weatherFetcher->fetchWeather("Guangzhou");
    }else if(city == "深圳"){
        weatherFetcher->fetchWeather("Shenzhen");
    }else if(city == "天津"){
        weatherFetcher->fetchWeather("Tianjin");
    }else if(city == "杭州"){
        weatherFetcher->fetchWeather("Hangzhou");
    }else if(city == "成都"){
        weatherFetcher->fetchWeather("Chengdu");
    }else if(city == "桂林"){
        weatherFetcher->fetchWeather("Guilin");
    }
}

// 更新 UI 中的天气信息显示
void MainWindow::updateWeatherDisplay(const QString &weather, double temp) {
    QString weatherInfo = QString("天气: %2")
                              .arg(weather);
    ui->weatherLabel->setText(weatherInfo);  // 将天气信息更新到标签
    QString tempInfo = QString("温度: %3 °C")
                           .arg(temp);
    ui->tempLabel->setText(tempInfo);  // 将温度信息更新到标签
}

void MainWindow::showYear() {//年视图
    // 创建 YearCalendar 窗口
    YearCalendar *yearCalendarWindow = new YearCalendar(2024, nullptr);  // 假设显示 2024 年的日历
    yearCalendarWindow->show();  // 显示年视图窗口

    //this->hide();  // 隐藏主窗口
}

void MainWindow::showWeek() {//周视图
    // 创建一个 WeekCalendar 窗口，显示当前周
    WeekCalendar *weekCalendarWindow = new WeekCalendar(nullptr);
    weekCalendarWindow->show();  // 显示年视图窗口

    //this->hide();// 隐藏主窗口
}

void MainWindow::showEvents() {//显示所有事件
    // 创建一个窗口，显示事件
    ShowEvents *ShowEventsWindow = new ShowEvents(nullptr);
    ShowEventsWindow->show();  // 显示窗口

    // 隐藏主窗口
    //this->hide();
}

void MainWindow::addEvent() {
    EventDialog dialog(this);
    QDate selectedDate = ui->calendarWidget->selectedDate();
    dialog.setSelectedDate(selectedDate);  // 设置默认日期为选中日期

    if (dialog.exec() == QDialog::Accepted) {
        Event newEvent = dialog.getEvent();

        //events.append(newEvent);//添加到events列表中

        showSelectedDateEvents(selectedDate);  // 更新事件列表，仅显示当前选中日期的事件

        // 将新事件存储到数据库中
        storage->addEvent(newEvent.getTitle(), newEvent.getDateTime(),
                         newEvent.getCategory(), newEvent.getDescription());
    }
    updateEventList();
}

void MainWindow::updateEventList() {
    QDate selectedDate = ui->calendarWidget->selectedDate(); //获取选中日期
    // 保存当前选中的事件的索引
    int currentIndex = ui->eventListWidget->currentRow();
    // 清空当前事件列表
    ui->eventListWidget->clear();

    // 从数据库获取所有事件
    QVector<Event> allEvents = storage->getAllEvents(); // 从数据库读取事件

    // 过滤和显示选中日期的事件
    for (const Event &event : allEvents) {
        if (event.getDateTime().date() == selectedDate) { // 仅显示选中日期的事件

            events.append(event);//选中日期的事件添加到events列表中

            QString displayText = QString("%1 - %2 (%3)")
                .arg(event.getTitle())
                .arg(event.getDateTime().toString("hh:mm"))
                .arg(event.getCategory());

            // 计算倒计时
            qint64 secondsToEvent = QDateTime::currentDateTime().secsTo(event.getDateTime());
            if (secondsToEvent > 0) {
                int hours = secondsToEvent / 3600;
                int minutes = (secondsToEvent % 3600) / 60;
                int seconds = secondsToEvent % 60;

                QString countdownText = QString("倒计时: %1小时 %2分钟 %3秒")
                    .arg(hours)
                    .arg(minutes)
                    .arg(seconds);
                displayText += " " + countdownText;
            } else {
                displayText += " (已过期)";
            }

            ui->eventListWidget->addItem(displayText);
        }
    }
    // 如果之前有选中的项，重新设置选中状态
    if (currentIndex >= 0 && currentIndex < ui->eventListWidget->count()) {
        ui->eventListWidget->setCurrentRow(currentIndex);
    }
}

void MainWindow::showSelectedDateEvents(const QDate &date) {
    selectedDate = date; // 更新当前选中的日期
    updateEventList(); // 更新事件列表
}

void MainWindow::checkUpcomingEvents() {
    for (auto it = events.begin(); it != events.end();) {
        if (it->getDateTime() <= QDateTime::currentDateTime()) { // 只在时间到达时通知
            QString title = it->getTitle();
            if (!notifiedEvents.contains(title)) {
                Notifier::showNotification(title + "即将到来!");
                notifiedEvents.insert(title); // 标记为已提醒
                it = events.erase(it); // 删除事件
            } else {
                ++it; // 如果已经提醒过，继续下一个事件
            }
        } else {
            ++it; // 继续下一个事件
        }
    }
    updateEventList(); // 更新事件列表
}

void MainWindow::showCountdown() {// 找到最近的事件
    // 从数据库获取所有事件
    QVector<Event> allEvents = storage->getAllEvents(); // 从数据库读取事件
    if (allEvents.isEmpty()) return;

    Event closestEvent = allEvents.first();
    // 过滤和显示选中日期的事件
    for (const Event &event : allEvents) {
        if (event.getDateTime() < closestEvent.getDateTime() &&
            event.getDateTime() > QDateTime::currentDateTime()) { // 仅显示选中日期的事件
            closestEvent = event;
        }
    }

    CountdownWindow *countdownWindow = new CountdownWindow(this);
    countdownWindow->startCountdown(closestEvent);
    countdownWindow->show();

    this->hide(); // 隐藏主窗口
}

//更新事件并保存到数据库
void MainWindow::editEvent(QListWidgetItem *item) {
    // 获取当前选中的事件项
    int index = ui->eventListWidget->row(item);
    if (index < 0 || index >= events.size()) return;

    // 获取当前选中事件
    EventDialog dialog(this);
    const Event &event = events[index];

    // 设置对话框的初始值
    dialog.setTitle(event.getTitle());
    dialog.setDateTime(event.getDateTime());
    dialog.setCategory(event.getCategory());
    dialog.setDescription(event.getDescription());

    // 如果用户确认修改
    if (dialog.exec() == QDialog::Accepted) {
        Event updatedEvent = dialog.getNewEvent(); // 获取更新后的事件

        // 更新本地事件列表
        events[index] = updatedEvent;

        // 更新数据库中的事件
        storage->updateEvent(updatedEvent);  // 假设SQLiteStorage类中有updateEvent方法

        // 刷新事件列表
        updateEventList();
    }
}

void MainWindow::deleteEvent() {
    // 获取当前选中的事件项
    QListWidgetItem *currentItem = ui->eventListWidget->currentItem();
    if (currentItem) {
        // 获取事件标题并去除空格
        QString title = currentItem->text().trimmed();
        qDebug() << "Attempting to delete event:" << title;

        // 从事件标题中提取第一个部分（假设标题按 " - " 分隔）
        QString eventTitle = title.split(" - ").first().trimmed();

        // 调用 SQLiteStorage 类的 deleteEvent 方法删除数据库中的事件
        storage->deleteEvent(eventTitle);  // 使用提取的标题部分进行删除

        // 刷新事件列表
        updateEventList();

    } else {
        QMessageBox::warning(this, "删除事件", "请选择要删除的事件。");
    }
}


