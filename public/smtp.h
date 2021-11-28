#ifndef SMTP_H
#define SMTP_H

#include<QByteArray>
#include<QString>
#include<QTcpSocket>
#include<QTime>

class Smtp
{
public:
    Smtp(QByteArray username,QByteArray password);
    ~Smtp();
    void send(QByteArray recvaddr,QString subject,QString content);
    static QString GenerateVarification();     // 生成随机验证码1000~9999

private:
    QTcpSocket * clientsocket;
    QByteArray username;
    QByteArray password;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject ="subject:";
    QString subject;                //主题
    QString content;                //发送内容
    QByteArray recvdata;            //接收到的数据
};

#endif // SMTP_H
