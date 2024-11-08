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
//#include "eventdialog.h"
//#include "ui_eventdialog.h"

//EventDialog::EventDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EventDialog) {
//    ui->setupUi(this);
//}

//EventDialog::~EventDialog() {
//    delete ui;
//}

//Event EventDialog::getEvent() const {
//    QString title = ui->titleLineEdit->text();
//    QDate date = ui->dateEdit->date();
//    QTime time = ui->timeEdit->time();
//    QString category = ui->categoryComboBox->currentText();
//    QString description = ui->descriptionTextEdit->toPlainText();

//    return Event(title, QDateTime(date, time), category, description);
//}


/*=================================================*/

//#include "eventdialog.h"
//#include "ui_eventdialog.h"

//EventDialog::EventDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::EventDialog) {
//    ui->setupUi(this);

//    // 连接“确定”按钮的信号
//    connect(ui->okButton, &QPushButton::clicked, this, [=]() {
//        accept();  // 接受对话框
//    });

//    // 连接“取消”按钮的信号
//    connect(ui->cancelButton, &QPushButton::clicked, this, &EventDialog::reject);
//}

//EventDialog::~EventDialog() {
//    delete ui;
//}

//Event EventDialog::getEvent() const {
//    Event event;
//    event.setTitle(ui->titleLineEdit->text());
//    event.setDateTime(QDateTime(ui->dateEdit->date(), ui->timeEdit->time()));
//    event.setCategory(ui->categoryComboBox->currentText());
//    event.setDescription(ui->descriptionTextEdit->toPlainText());

//    // 处理提醒时间
//    QTime remindTime = ui->remindTimeEdit->time();
//    event.setRemindTime(remindTime); // 假设 Event 类有 setRemindTime 方法

//    return event;
//}

/*22222222222222222222222222222222222222222222222222*/


#include "eventdialog.h"
#include "ui_eventdialog.h"

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog) {
    ui->setupUi(this);

    // 连接“确定”按钮的信号
    connect(ui->okButton, &QPushButton::clicked, this, [=]() {
        accept();  // 接受对话框
    });

    // 连接“取消”按钮的信号
    connect(ui->cancelButton, &QPushButton::clicked, this, &EventDialog::reject);
}

EventDialog::~EventDialog() {
    delete ui;
}

Event EventDialog::getEvent() const {
    Event event;
    event.setTitle(ui->titleLineEdit->text());
    event.setDateTime(QDateTime(ui->dateEdit->date(), ui->timeEdit->time()));
    event.setCategory(ui->categoryComboBox->currentText());
    event.setDescription(ui->descriptionTextEdit->toPlainText());

    // 处理提醒时间
    QTime remindTime = ui->remindTimeEdit->time();
    event.setRemindTime(remindTime); // 假设 Event 类有 setRemindTime 方法

    return event;
}

void EventDialog::setTitle(const QString &title) {
    ui->titleLineEdit->setText(title);
}

void EventDialog::setDateTime(const QDateTime &dateTime) {
    ui->dateEdit->setDate(dateTime.date());
    ui->timeEdit->setTime(dateTime.time());
}

void EventDialog::setCategory(const QString &category) {
    int index = ui->categoryComboBox->findText(category);
    if (index != -1) {
        ui->categoryComboBox->setCurrentIndex(index);
    }
}

void EventDialog::setDescription(const QString &description) {
    ui->descriptionTextEdit->setPlainText(description);
}

void EventDialog::setRemindTime(const QTime &remindTime) {
    ui->remindTimeEdit->setTime(remindTime);
}
