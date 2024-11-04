

/*=================================================*/

//#ifndef EVENTDIALOG_H
//#define EVENTDIALOG_H

//#include <QDialog>
//#include "event.h"

//namespace Ui {
//class EventDialog;
//}

//class EventDialog : public QDialog {
//    Q_OBJECT

//public:
//    explicit EventDialog(QWidget *parent = nullptr);
//    ~EventDialog();
//    Event getEvent() const;  // 获取事件信息

//    void setTitle(const QString &title);
//    void setDateTime(const QDateTime &dateTime);
//    void setCategory(const QString &category);
//    void setDescription(const QString &description);
//    void setRemindTime(const QTime &remindTime);

//private:
//    Ui::EventDialog *ui;
//};

//#endif // EVENTDIALOG_H


/*22222222222222222222222222222222222222222222222222*/


#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "event.h"

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog {
    Q_OBJECT

public:
    explicit EventDialog(QWidget *parent = nullptr);
    ~EventDialog();
    Event getEvent() const;  // 获取事件信息

    void setTitle(const QString &title);
    void setDateTime(const QDateTime &dateTime);
    void setCategory(const QString &category);
    void setDescription(const QString &description);
    void setRemindTime(const QTime &remindTime);

    void setSelectedDate(const QDate &date); // 添加此行声明函数


private:
    Ui::EventDialog *ui;
};

#endif // EVENTDIALOG_H
