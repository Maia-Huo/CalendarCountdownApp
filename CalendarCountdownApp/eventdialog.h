// dialogs/eventdialog.h
#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "event.h"

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(QWidget *parent = nullptr);
    ~EventDialog();
    Event getEvent() const;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::EventDialog *ui;
    Event event;
};

#endif // EVENTDIALOG_H
