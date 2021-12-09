#include "log_in_window.h"
#include "game/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWindow w;
    MainWindow mainWindow;
    w.show();
    mainWindow.show();
    return a.exec();
}
