#ifndef FORGET_WINDOW_H
#define FORGET_WINDOW_H

#include "public/connection.h"
#include "public/smtp.h"

#include <QMainWindow>

namespace Ui {
class ForgetWindow;
}

class ForgetWindow : public QMainWindow
{
    Q_OBJECT    
public:
    explicit ForgetWindow(QWidget *parent = nullptr);
    ~ForgetWindow();

public slots:
    void SendVerify();                 // 发送注册邮箱用验证码
    void CheckModification();          // 确保发送可用的注册信息
    void readMeg(QString);             // 接收来自服务器的数据

private:
    Ui::ForgetWindow *ui;
    static QString _verification_code;
};

#endif // FORGET_WINDOW_H
