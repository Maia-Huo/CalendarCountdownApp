#include <QApplication>
#include "mainwindow.h"
#include "login.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    //mainWindow.show();

    LoginDialog login;
    login.show();

    return app.exec();
}
