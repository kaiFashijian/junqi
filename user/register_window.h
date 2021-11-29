#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include "public/smtp.h"
#include "public/connection.h"

#include <QMainWindow>
#include <QPushButton>
#include <QtGlobal>
#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void FeedbackMessage(QString msg);  // 展示各种反馈信息

private slots:
    void SendVerify();                  // 发送注册邮箱用验证码
    void CheckRegisteration();          // 确保发送可用的注册信息
    void readMessage(QString);          // 读取来自服务器的内容
private:
    Ui::RegisterWindow *ui;
    static QString _verification_code;
};

#endif // REGISTER_WINDOW_H
