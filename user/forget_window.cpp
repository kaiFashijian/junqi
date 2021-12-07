#include "forget_window.h"
#include "ui_forget_window.h"

QString ForgetWindow::_verification_code = "XXXX";

ForgetWindow::ForgetWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgetWindow)
{
    ui->setupUi(this);

    Connection *cont = Connection::getConnection();

    // 跳转到登录界面
    connect(ui->pushButton_ret, &QPushButton::clicked, parent, [=](){
        parent->show();
        this->hide();
    });

    // 发送验证码
    connect(ui->pushButton_send, &QPushButton::clicked, this, &ForgetWindow::SendVerify);
    // 检查注册信息
    connect(ui->pushButton_modify, &QPushButton::clicked, this, &ForgetWindow::CheckModification);
    // 接收来自服务器的数据
    connect(cont, &Connection::UMsiganl, this, &ForgetWindow::readMeg);
}

ForgetWindow::~ForgetWindow()
{
    delete ui;
}

void ForgetWindow::FeedbackMessage(QString msg) {
    QMessageBox::critical(this, "修改错误", msg);
}

void ForgetWindow::CheckModification()
{
    QString mail = ui->lineEdit_mail->text();
    QString new_pwd = ui->lineEdit_pwd_new->text();
    QString ack_pwd = ui->lineEdit_pwd_ack->text();
    QString verification_code = ui->lineEdit_verify->text();

    if (new_pwd == "" || ack_pwd == "" || mail == "" || verification_code == "") {
        FeedbackMessage("输入内容不能为空");
        return;
    }

    // 检查两次密码是否相同
    if (new_pwd != ack_pwd)
    {
        FeedbackMessage("两次密码不一样");
        return;
    }

    // 检查邮箱验证码
    if (_verification_code != verification_code)
    {
        FeedbackMessage("邮箱验证码出错");
        return;
    }

    //封装用户修改密码网络包 "U&R&邮箱&新密码"
    QString str = "U&M&";
    str.append(mail).append("&").append(new_pwd);
    //发送包
    Connection *cont = Connection::getConnection();
    cont->sendMsg(str);
}

void ForgetWindow::SendVerify()
{
    //检查邮箱合理性 "2019141460217@stu.scu.edu.cn"
    QString mail_address = ui->lineEdit_mail->text();

    //存放在本地的验证码
    _verification_code = Smtp::GenerateVarification();

    //第一个参数是发送者邮箱，第二个授权码，并不是邮箱密码
    Smtp smtp("2387355088@qq.com","qizabxcdsxfldihi");
    smtp.send(mail_address.toUtf8(), "JunChess用户注册验证码", QString("验证码是%1，如非本人操作请忽略这封邮件").arg(_verification_code));
}

void ForgetWindow::readMeg(QString msg)
{
    if (msg == "S") {
        FeedbackMessage("修改密码成功，请重新登录");
        emit ui->pushButton_ret->clicked();
    } else {
        FeedbackMessage("修改密码失败，请重新尝试");
    }
}
