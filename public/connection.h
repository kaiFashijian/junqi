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


public slots:
    void readMsg();

private:
    static const int port;
    static const QString hostname;
    static QTcpSocket *client;
    static Connection *cont;
};

#endif // CONNECTION_H
