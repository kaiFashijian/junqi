#include "connection.h"

// 静态变量初始化
const int Connection::port = 6080;
const QString Connection::hostname = "127.0.0.1";
QTcpSocket *Connection::client = nullptr;
Connection *Connection::cont = nullptr;

Connection *Connection::getConnection() {
    if (cont == nullptr) {
        cont = new Connection();
        cont->client = new QTcpSocket();
        cont->client->connectToHost(hostname, port);
        // 绑定读信号（服务器有数据返回触发），调用readMsg槽函数发送到各个模块
        connect(cont->client, SIGNAL(readyRead()), cont, SLOT(readMsg()));
        // 绑定断线信号，调用reConnect槽函数进行重连
        connect(cont->client, &QTcpSocket::disconnected, cont, &Connection::reConnect);
    }
    return cont;
}

void Connection::sendMsg(QString msg) {
    QByteArray data = msg.toUtf8();
    client->flush();
    client->write(data);
}

void Connection::reConnect() {
    cont->client->abort();
    cont->client->connectToHost(hostname, port);
}

void Connection::readMsg() {
    QString msg = client->readAll();
    //将接收到的数据存放到变量中
    QStringList data = msg.split('&');

    if (data[0] == "U") { // 用户模块
        if (data[1] == "L") { // 登录
            emit Connection::ULsignal(data[2]);
        } else if (data[1] == "R") { // 注册
            emit Connection::URsignal(data[2]);
        } else if (data[1] == "M") { // 修改密码
            emit Connection::UMsiganl(data[2]);
        }
    } else if (data[0] == "R") { // 房间模块

    } else if (data[0] == "G") { // 游戏模块

    } else if (data[0] == "S") { // 辅助模块

    }

    client->flush();
}
