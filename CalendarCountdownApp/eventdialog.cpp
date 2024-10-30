//#include "eventdialog.h"
//#include "ui_eventdialog.h"

//EventDialog::EventDialog(QWidget *parent)
//    : QDialog(parent), ui(new Ui::EventDialog) {
//    ui->setupUi(this);
//}

//EventDialog::~EventDialog() {
//    delete ui;
//}

//Event EventDialog::getEvent() const {
//    // 获取用户输入的事件数据
//    return Event("Sample Event", QDateTime::currentDateTime(), "工作");
//}

//void EventDialog::setEvent(const Event &event) {
//    // 设置事件用于编辑
//}


// eventdialog.cpp
#include "eventdialog.h"
#include "ui_eventdialog.h"

EventDialog::EventDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EventDialog) {
    ui->setupUi(this);
}

EventDialog::~EventDialog() {
    delete ui;
}

Event EventDialog::getEvent() const {
    QString title = ui->titleLineEdit->text();
    QDate date = ui->dateEdit->date();
    QTime time = ui->timeEdit->time();
    QString category = ui->categoryComboBox->currentText();
    QString description = ui->descriptionTextEdit->toPlainText();

    return Event(title, QDateTime(date, time), category, description);
}
