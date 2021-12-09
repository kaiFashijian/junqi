#ifndef DATING_H
#define DATING_H

#include <QWidget>
#include "qlistwidget.h"
#include "room.h"
#include <qmessagebox.h>
#include <QPushButton>
#include <qtimer.h>
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
    room* room_a;
    int his_score;
    QString his_name;
    QString room_id;

private slots:
    void show_room();//刷新房间列表信息
    void on_roomtable_cellClicked(int row, int column);
    void  read_room(QString msg);//获取房间信息



private:

    Ui::dating *ui;
    QStringList room_arr;
    int room_max=-1;    //房间数量
};

#endif // DATING_H
