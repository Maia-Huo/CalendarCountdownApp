#include "notifier.h"
#include <QMessageBox>

void Notifier::showNotification(const QString &message) {
    QMessageBox::information(nullptr, "提醒信息", message);
}
