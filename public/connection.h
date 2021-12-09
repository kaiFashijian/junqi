#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

class Connection : public QObject
{
    Q_OBJECT
public:
    ~Connection() = default;
    static Connection *getConnection();
    void sendMsg(QString msg);


private:
    Connection() = default;

signals:
    void URsignal(QString);
    void ULsignal(QString);
    void UMsiganl(QString);
    void TestSignal(QString);
    void RNsignal(QString);//请求房间信号
    void RJsignal(QString);  //加入房间成功信号
    void ROsignal(QString);  //对方准备
    void RBsignal(QString);  //有一个人退出信号
    void RCSsignal(); //创建成功信号
    void RCWsignal(); //创建失败信号
    void RJSsignal();//加入房间成功信号
    void RJWsignal();//加入房间失败信号

public slots:
    void readMsg();
    void reConnect();

private:
    static const int port;
    static const QString hostname;
    static QTcpSocket *client;
    static Connection *cont;
};

#endif // CONNECTION_H
