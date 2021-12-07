#ifndef DATING_H
#define DATING_H

#include <QWidget>
#include "qlistwidget.h"
#include "room.h"
#include <qmessagebox.h>
#include <QPushButton>
#include <qtimer.h>
//#include"createRoom.h"
#include "public/connection.h"
#include "user/user.h"

namespace Ui {
class dating;
}

class dating : public QWidget
{
    Q_OBJECT

public:
    explicit dating(QWidget *parent = nullptr);
    ~dating();
    int room_num=-1;
    void showEvent(QShowEvent *);
    QTimer* timer;

private slots:
    void show_room();//刷新房间列表信息
    void on_roomtable_cellClicked(int row, int column);
    void  read_room();//获取房间信息


private:
    room* room_a;
    Ui::dating *ui;
    //createRoom* create_b;
};

#endif // DATING_H
