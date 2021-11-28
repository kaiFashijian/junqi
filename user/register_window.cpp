#include "register_window.h"
#include "ui_register_window.h"

QString RegisterWindow::_verification_code = "XXXX";

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    // 建立与服务器的连接
    Connection *cont = Connection::getConnection();

    // 跳转到登录界面
    connect(ui->pushButton_ret, &QPushButton::clicked, parent, [=](){
        parent->show();
        this->hide();
    });
    // 发送验证码
    connect(ui->pushButton_send, &QPushButton::clicked, this, &RegisterWindow::SendVerify);
    // 检查注册信息
    connect(ui->pushButton_reg, &QPushButton::clicked, this, &RegisterWindow::CheckRegisteration);
    // 接收来自服务器的反馈信息
    connect(cont, &Connection::URsignal, this, &RegisterWindow::readMessage);
    connect(cont, &Connection::TestSignal, this, &RegisterWindow::readMessage);

}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::FeedbackMessage(QString msg)
{
    qDebug() << msg;
}

void RegisterWindow::SendVerify()
{
    //检查邮箱合理性 "2019141460217@stu.scu.edu.cn"
    QString mail_address = ui->lineEdit_mail->text();

    //存放在本地的验证码
    _verification_code = Smtp::GenerateVarification();

    //第一个参数是发送者邮箱，第二个授权码，并不是邮箱密码
    Smtp smtp("2387355088@qq.com","qizabxcdsxfldihi");
    smtp.send(mail_address.toUtf8(), "JunChess用户注册验证码", QString("验证码是%1，如非本人操作请忽略这封邮件").arg(_verification_code));
}

void RegisterWindow::CheckRegisteration()
{
    QString mail = ui->lineEdit_mail->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString ack_pwd = ui->lineEdit_ack_pwd->text();
    QString verification_code = ui->lineEdit_verify->text();

    // 检查两次密码是否相同
    if (pwd != ack_pwd)
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

    //封装用户注册网络包 "U&R&邮箱&密码"
    QString str = "U&R&";
    str.append(mail).append("#").append(pwd);
    //发送包
    Connection *cont = Connection::getConnection();
    cont->sendMsg(str);
    //cont->readMsg();
}

void RegisterWindow::readMessage(QString msg)
{
    qDebug() << msg;
}
