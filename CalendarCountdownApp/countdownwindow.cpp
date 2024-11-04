//#include "countdownwindow.h"
//#include "ui_countdownwindow.h"

//CountdownWindow::CountdownWindow(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::CountdownWindow),
//    countdownTimer(new QTimer(this)) {
//    ui->setupUi(this);


//    connect(countdownTimer, &QTimer::timeout, this, &CountdownWindow::updateCountdown);
//    connect(ui->closeButton, &QPushButton::clicked, this, &CountdownWindow::on_closeButton_clicked);
//}

//CountdownWindow::~CountdownWindow() {
//    delete ui;
//}

//void CountdownWindow::startCountdown(const QDateTime &eventTime) {
//    this->eventTime = eventTime;
//    countdownTimer->start(1000); // 每秒更新
//    updateCountdown();
//}

//void CountdownWindow::updateCountdown() {
//    qint64 secondsToEvent = QDateTime::currentDateTime().secsTo(eventTime);
//    if (secondsToEvent > 0) {
//        int hours = secondsToEvent / 3600;
//        int minutes = (secondsToEvent % 3600) / 60;
//        int seconds = secondsToEvent % 60;
//        ui->countdownLabel->setText(QString("倒计时: %1小时 %2分钟 %3秒")
//                                      .arg(hours).arg(minutes).arg(seconds));
//    } else {
//        ui->countdownLabel->setText("时间到！");
//        countdownTimer->stop(); // 停止计时器
//    }
//}

//void CountdownWindow::on_closeButton_clicked() {
//    this->close(); // 关闭倒计时窗口

//    // 显示主窗口
//    if (parentWidget()) {
//        parentWidget()->show(); // 显示主窗口
//    }
//}


#include "countdownwindow.h"
#include "ui_countdownwindow.h"
#include <QMouseEvent>

CountdownWindow::CountdownWindow(QWidget *parent) :
    QDialog(parent), // 使用 parent 作为父窗口
    ui(new Ui::CountdownWindow),
    countdownTimer(new QTimer(this)),
    isDragging(false) {
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);

    QString styleSheet = R"(
        #CountdownWindow {
            background-color: rgba(50, 50, 50, 200);
            border-radius: 10px;
        }
        #countdownLabel {
            color: #FF6347;
            font-size: 16px;
            font-weight: bold;
            padding: 10px;
        }
        #closeButton {
            background-color: #FF6347;
            color: white;
            border-radius: 5px;
            padding: 5px 10px;
            font-size: 14px;
        }
        #closeButton:hover {
            background-color: #FF4500;
        }
    )";
    setStyleSheet(styleSheet);

    connect(countdownTimer, &QTimer::timeout, this, &CountdownWindow::updateCountdown);
    connect(ui->closeButton, &QPushButton::clicked, this, &CountdownWindow::on_closeButton_clicked);
}

CountdownWindow::~CountdownWindow() {
    delete ui;
}

void CountdownWindow::startCountdown(const QDateTime &eventTime) {
    this->eventTime = eventTime;
    countdownTimer->start(1000);
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
        countdownTimer->stop();
    }
}

void CountdownWindow::on_closeButton_clicked() {
    this->close(); // 关闭倒计时窗口

    // 显示主窗口
    if (parentWidget()) {
        parentWidget()->show(); // 显示主窗口
    }
}

// 鼠标拖动事件处理
void CountdownWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void CountdownWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        this->move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void CountdownWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}
