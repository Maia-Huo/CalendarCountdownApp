//#ifndef EVENTDIALOG_H
//#define EVENTDIALOG_H

//#include <QDialog>
//#include "event.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class EventDialog; }
//QT_END_NAMESPACE

//class EventDialog : public QDialog {
//    Q_OBJECT

//public:
//    EventDialog(QWidget *parent = nullptr);
//    ~EventDialog();
//    Event getEvent() const; // 获取用户输入的事件
//    void setEvent(const Event &event); // 设置事件用于编辑

//private:
//    Ui::EventDialog *ui;
//};

//#endif // EVENTDIALOG_H


// eventdialog.h
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

//    Event getEvent() const;

//private:
//    Ui::EventDialog *ui;
//};

//#endif // EVENTDIALOG_H


/*=================================================*/

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

private:
    Ui::EventDialog *ui;
};

#endif // EVENTDIALOG_H


/*22222222222222222222222222222222222222222222222222*/
