// dialogs/eventdialog.cpp
#include "eventdialog.h"
#include "ui_eventdialog.h"

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    ui->remindTimeEdit->setTime(QTime::currentTime());
}

EventDialog::~EventDialog()
{
    delete ui;
}

Event EventDialog::getEvent() const
{
    return event;
}

void EventDialog::on_okButton_clicked()
{
    event.title = ui->titleLineEdit->text();
    event.date = ui->dateEdit->date().toString("yyyy-MM-dd");
    event.time = ui->timeEdit->time().toString("HH:mm");
    event.category = ui->categoryComboBox->currentText();
    event.remindTime = ui->remindTimeEdit->time().toString("HH:mm");
    event.description = ui->descriptionTextEdit->toPlainText();
    accept();
}

void EventDialog::on_cancelButton_clicked()
{
    reject();
}
