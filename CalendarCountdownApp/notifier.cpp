#include "notifier.h"
#include <QMessageBox>

void Notifier::showNotification(const QString &message) {
    QMessageBox::information(nullptr, "Notification", message);
}


/*=================================================*/
