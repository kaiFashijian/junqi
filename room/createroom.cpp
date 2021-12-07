#include "createRoom.h"
#include "ui_createroom.h"

createRoom::createRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createRoom)
{
    ui->setupUi(this);
    room_a=new room();

    //创建房间
    connect(ui->pushButton,&QPushButton::clicked,room_a, [=](){

        room_a->show();
        //传值给服务器
        this->close();
    });

    //退出
    connect(ui->pushButton_2,&QPushButton::clicked,parent,[=](){
        parent->show();
        this->hide();
        //传值给服务器，告知已退出该房间
    });

}

createRoom::~createRoom()
{
    delete ui;
}
