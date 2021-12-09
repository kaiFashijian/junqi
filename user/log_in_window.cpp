#include "log_in_window.h"
#include "ui_log_in_window.h"

LogInWindow::LogInWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogInWindow)
{
    // 初始化与服务器的连接
    Connection *cont = Connection::getConnection();

    ui->setupUi(this);

    // 辅助功能_修改信息
    connect(ui->action_info, &QAction::triggered, [=](){
        Information *info = new Information(this);
        info->exec();
    });

    // 辅助功能_反馈信息
    connect(ui->action_advice, &QAction::triggered, [=](){
        Advice *advice = new Advice(this);
        advice->exec();
    });

    // 两个子窗口 注册 和 修改密码 界面
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
       // TODO（@li@yang）
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
    extern User local_user;
    QStringList attributes_arr = msg.split('#');
    // "U&L&S#name#uid#scores#friend#icon"
    if (attributes_arr[0] == "S") {
        local_user.name = attributes_arr[1];
        local_user.uid = attributes_arr[2];
        local_user.scores = attributes_arr[3].toInt();
        local_user.friends_list = attributes_arr[4].split(' '); // TODO(@ye):好友之间的分隔符是什么
        local_user.icon_url = attributes_arr[5];
        // TODO(@li@ye@yang): 登录成功后如何跳转到游戏大厅

    } else { // "U&L&W#wrong_message" TODO(@li)
        FeedbackMessage("账号不存在或者账号密码不匹配，请重新尝试");
    }



}
