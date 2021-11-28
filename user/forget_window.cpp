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

void ForgetWindow::CheckModification()
{
    // TODO(@li)
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
    // TODO(@li)
}
