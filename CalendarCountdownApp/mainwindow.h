#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QCalendarWidget>
#include <QLabel>
#include <QListWidget>

//导入其他.h文件


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calendarDataClicked(const QDate &date);
    void on_addEventButton_clicked();
    void updateEventList(const QDate &date);
    void updateCountdown();

private:
    Ui::MainWindow *ui;
    Database db;
    Notifier notifier;
    QTimer *countdownTimer;

    void setupConnections();
    void loadEvents(const QDate &date);
};

#endif // MAINWINDOW_H
