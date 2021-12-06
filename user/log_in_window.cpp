#include "log_in_window.h"
#include "ui_log_in_window.h"

LogInWindow::LogInWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogInWindow)
{
    // 初始化与服务器的连接
    Connection *cont = Connection::getConnection();

    ui->setupUi(this);

    reg = new RegisterWindow(this);
    modify = new ForgetWindow(this);

    // 跳转到注册界面
    connect(ui->pushButton_reg, &QPushButton::clicked, reg, [=](){
        reg->show();
        this->hide();
    });

    // 跳转到修改密码界面
    connect(ui->pushButton_modify, &QPushButton::clicked, modify, [=](){
        modify->show();
        this->hide();
    });

    // 登录成功后跳转到游戏大厅界面
    connect(ui->pushButton_log_in, &QPushButton::clicked, this, [=](){
       // TODO（@yang）
       auto roomWindow = new dating();
       roomWindow->show();
       this->close();
    });

    // 接收来自服务器的消息
    connect(cont, &Connection::ULsignal, this, &LogInWindow::readMsg);
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::CheckLogIn() {
    QString mail = ui->lineEdit_mail->text();
    QString pwd = ui->lineEdit_pwd->text();

    if (mail == "" || pwd == "") {
       FeedbackMessage("输入内容不能为空");
       return;
    }

    //封装用户登录网络包 "U&L&邮箱&密码"
    QString str = "U&R&";
    str.append(mail).append("&").append(pwd);
    //发送包
    Connection *cont = Connection::getConnection();
    cont->sendMsg(str);
}

void LogInWindow::FeedbackMessage(QString msg) {
    QMessageBox::critical(this, "登录错误", msg);
}

void LogInWindow::readMsg(QString msg)
{
    // TODO(@li)

}
