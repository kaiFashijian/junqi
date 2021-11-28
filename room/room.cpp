#include "room.h"
#include "ui_room.h"


room::room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::room)
{
    ui->setupUi(this);

    //退出房间
    connect(ui->exit_button,&QPushButton::clicked,parent,[=](){
        parent->show();
        this->close();
        //传值给服务器，告知已退出该房间

    });

    //准备游戏
    connect(ui->ready_button,&QPushButton::clicked,this,[=](){
        ui->my_ready_label->setText("         已准备");
        //传值给服务器，告知已准备

    });

    //像服务器请求双方头像、昵称、积分

}

room::~room()
{
    delete ui;
}

