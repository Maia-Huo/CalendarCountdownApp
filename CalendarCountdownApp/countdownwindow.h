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

private:
    Ui::CountdownWindow *ui;
    QTimer *countdownTimer;
    QDateTime eventTime;
};

#endif // COUNTDOWNWINDOW_H
