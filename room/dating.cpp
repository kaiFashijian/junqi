#include "dating.h"
#include "ui_dating.h"



dating::dating(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dating)
{
    ui->setupUi(this);
    room_a = new room(this);

    //选择房间
    //函数不会写，在下面

    //加入房间
    connect(ui->join_button, &QPushButton::clicked, room_a, [=](){
        if(room_num!=-1){
            this->hide();
            room_a->show();
        }
        //传值给服务器，告知服务器进入哪个房间，房间号为room_num
    });

    //创建房间
    connect(ui->create_button,&QPushButton::clicked,room_a, [=](){
        //向服务器提出创建申请，应该会返回房间号
        //room_num=
        room_a->show();

    });


    //显示大厅列表
//    connect(this->show(),,ui->roomtable,[=](){
//        //向服务器提出请求，服务器返回房间列表
//        ;
//    });

    //显示好友列表

    //显示头像，昵称，积分
}

dating::~dating()
{
    delete ui;
}

void dating::on_roomtable_cellClicked(int row, int column)
{
         room_num=row;//得到进入哪个房间
}
