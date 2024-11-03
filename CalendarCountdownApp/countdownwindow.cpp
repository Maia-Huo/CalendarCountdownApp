#include "countdownwindow.h"
#include "ui_countdownwindow.h"

CountdownWindow::CountdownWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountdownWindow),
    countdownTimer(new QTimer(this)) {
    ui->setupUi(this);
    connect(countdownTimer, &QTimer::timeout, this, &CountdownWindow::updateCountdown);
    connect(ui->closeButton, &QPushButton::clicked, this, &CountdownWindow::on_closeButton_clicked);
}

CountdownWindow::~CountdownWindow() {
    delete ui;
}

void CountdownWindow::startCountdown(const QDateTime &eventTime) {
    this->eventTime = eventTime;
    countdownTimer->start(1000); // 每秒更新
    updateCountdown();
}

void CountdownWindow::updateCountdown() {
    qint64 secondsToEvent = QDateTime::currentDateTime().secsTo(eventTime);
    if (secondsToEvent > 0) {
        int hours = secondsToEvent / 3600;
        int minutes = (secondsToEvent % 3600) / 60;
        int seconds = secondsToEvent % 60;
        ui->countdownLabel->setText(QString("倒计时: %1小时 %2分钟 %3秒")
                                      .arg(hours).arg(minutes).arg(seconds));
    } else {
        ui->countdownLabel->setText("时间到！");
        countdownTimer->stop(); // 停止计时器
    }
}

void CountdownWindow::on_closeButton_clicked() {
    this->close();
}
