#include "room.h"
#include "ui_room.h"


room::room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::room)
{
    ui->setupUi(this);
    //初始化定时器
    timer=new QTimer();
     timer->start(2000);


    //退出房间
    connect(ui->exit_button,&QPushButton::clicked,parent,[=](){
        parent->show();
        this->hide();
        //传值给服务器，告知已退出该房间
    });



    //准备游戏
    connect(ui->ready_button,&QPushButton::clicked,this,[=](){
        ui->my_ready_label->setText("         已准备");
        ready_num+=1;
        //测试
        //enter_game();
        //传值给服务器，告知已准备

    });

    //向服务器请求双方头像、昵称、积分

    //进入游戏
    connect(timer,SIGNAL(timeout()),this,SLOT(enter_game()));
}

room::~room()
{
    delete ui;
}

void room::showEvent(QShowEvent *){
   ready_num=1;//1为测试
   timer->start();
}


//进入游戏
void room::enter_game(){
//    timer->stop();
    if(ready_num>=2){
        game.show();
        this->hide();
    }
    timer->stop();
//    timer->start();
}

//退出房间
//void room::on_exit_button_clicked()
//{
//    emit back();
//}


