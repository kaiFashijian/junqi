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

    // 初始化与服务器的连接
    Connection *cont = Connection::getConnection();

     //退出房间
    connect(ui->exit_button,&QPushButton::clicked,parent,[=](){
        parent->show();
        this->hide();
        //传值给服务器，其中包房间号+自己的uid，告知已退出该房间
        QString strB="R&B&";
        strB.append(room_id).append("&").append(local_user.uid);
        cont->sendMsg(strB);
    });



    //准备游戏
    connect(ui->ready_button,&QPushButton::clicked,this,[=](){
        ui->my_ready_label->setText("         已准备");
        ready_num+=1;

        //传值给服务器，告知已准备
        QString strO="R&O";
        strO.append(local_user.uid);
        cont->sendMsg(strO);

        //测试
        //enter_game();
    });

    //对方准备后改变信息
    connect(cont, &Connection::ROsignal, this,&room::he_ready);

    //加入成功后获得对方头像等信息
    connect(cont, &Connection::RJsignal, this,&room::join_room_and_get_info);
    //join_room_and_get_info("小羊#1500#123456");  //test

    //进入游戏
    connect(timer,SIGNAL(timeout()),this,SLOT(enter_game()));

    //接收到另一个人的退出的信号
   // connect(cont, &Connection::RBsignal, this,&room::host_back);
    connect(cont, &Connection::RBsignal, this,[=](QString msg){
        QStringList info_arr=msg.split("#");
        if(info_arr[0]==room_id){
           // if(info_arr[1]==)  //其实不用判断id了
            if(is_owner==1){    //房主退出
                QMessageBox::information(NULL, "", "房主退出房间，将返回大厅");
                is_owner=-1;
                parent->show();
                this->close(); //or hide?
            }
            else if(is_owner==0){   //自己是房主，另一个退了
                //清空信息
                ui->his_name->setText("");
                ui->his_score->setText("");
                ui->his_ready_label->setText("准备信息");
                //头像还未做
            }
        }
    });


}

room::~room()
{
    delete ui;
}

void room::showEvent(QShowEvent *){
   ready_num=1;//1为测试
   timer->start();
   //显示自己信息
   ui->my_name->setText(local_user.name);
   ui->my_score->setText(QString::number(local_user.scores));
   //头像还未实现
   //ui->his_head->
}

//对方准备后改变信息
void room::he_ready(QString msg){
    QString one_name=msg;
    if(one_name==his_name){
         ui->his_ready_label->setText("         已准备");
         ready_num+=1;
    }
}



//进入游戏
void room::enter_game(){
//    timer->stop();
    if(ready_num>=2){
        //需要告知服务器进入游戏
        Connection *cont = Connection::getConnection();
        QString strG="R&G";
        //房间号是房主的名字
        strG.append(room_id);
        cont->sendMsg(strG);
        game.show();
        this->hide();
        timer->stop();
    }
}

//加入房间并获取对方信息
void room::join_room_and_get_info(QString msg){
    //房间号#对方昵称&#对方积分#对方头像url
    QStringList his_info=msg.split("#");
    if(his_info[0]==room_id){
        ui->his_name->setText(his_info[0]);
        his_name=his_info[0];
        ui->his_score->setText(his_info[1]);
        //头像还未实现
        //ui->his_head->
    }

}




