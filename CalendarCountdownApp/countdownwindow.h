#ifndef COUNTDOWNWINDOW_H
#define COUNTDOWNWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class CountdownWindow;
}

class CountdownWindow : public QDialog {
    Q_OBJECT

public:
    explicit CountdownWindow(QWidget *parent = nullptr);
    ~CountdownWindow();
    void startCountdown(const QDateTime &eventTime);

private slots:
    void updateCountdown();
    void on_closeButton_clicked();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::CountdownWindow *ui;
    QTimer *countdownTimer;
    QDateTime eventTime;

    bool isDragging;          // 标记是否正在拖动
        QPoint dragPosition;      // 记录拖动位置
};

#endif // COUNTDOWNWINDOW_H
