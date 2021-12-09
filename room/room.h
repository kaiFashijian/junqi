#ifndef ROOM_H
#define ROOM_H

#include <QDialog>
#include "game/mainwindow.h"
#include <qtimer.h>
#include "public/connection.h"
#include "user/user.h"
#include <qmessagebox.h>
#include "user/user.h"

namespace Ui {
class room;
}

class room : public QDialog
{
    Q_OBJECT

public:
    explicit room(QWidget *parent = nullptr);
    ~room();
    int ready_num=0;//1为测试时使用，实际应为0
    QTimer* timer;
    void showEvent(QShowEvent *);
    //int his_score=-1;
    QString his_name;
    QString room_id;
    int is_owner=-1;//0是房主，1是其他

private slots:
    void enter_game();

    void he_ready(QString msg);//对方准备后改变信息

    void join_room_and_get_info(QString msg); //加入房间并获取对方信息

    //void host_back(QString msg); //房主退出,目前未使用


private:
    Ui::room *ui;
    MainWindow game;

signals:
    void back();


};

#endif // ROOM_H
