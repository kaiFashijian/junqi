#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "forget_window.h"
#include "register_window.h"
#include "room/dating.h"
#include "public/connection.h"
#include "public/public.h"

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class LogInWindow; }
QT_END_NAMESPACE

class LogInWindow : public QMainWindow
{
    Q_OBJECT

public:
    LogInWindow(QWidget *parent = nullptr);
    ~LogInWindow();
    void FeedbackMessage(QString msg);


private slots:
    void readMsg(QString);
    void CheckLogIn();

signals:
    void GameShow();

private:
    Ui::LogInWindow *ui;
    RegisterWindow *reg;
    ForgetWindow *modify;
};
#endif // LOGINWINDOW_H
