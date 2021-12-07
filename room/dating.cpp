#include "dating.h"
#include "ui_dating.h"



dating::dating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dating)
{
    ui->setupUi(this);
    room_a = new room(this);
    //create_b=new createRoom(this);

    // 初始化与服务器的连接
    Connection *cont = Connection::getConnection();
    //向服务器要求房间信息
    QString str = "R&R&R";
    cont->sendMsg(str);


    //初始化定时器
    timer=new QTimer();
     timer->start(2000);

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
        //向服务器提出创建申请，向服务器发送房主名称和UID，应该会返回房间号
        QString strC="R&C&";
        // strC.append().append("&").append();
        cont->sendMsg(strC);
        //room_num=
        this->hide();
        room_a->show();
    });


    //显示大厅列表
    //connect(timer,SIGNAL(timeout()),this,SLOT(show_room()));
    connect(cont, &Connection::RRRsignal, this,&dating::read_room);

    //显示好友列表
    connect(timer,SIGNAL(timeout()),this,SLOT(show_friend()));

    //显示头像，昵称，积分
    //在showevent内

    //接受back信号显示窗口
//    connect(this,SIGNAL(back()),this,SLOT([=](){
//        this->show();
//    }));
}

dating::~dating()
{
    delete ui;
}

void dating::on_roomtable_cellClicked(int row, int column)
{
         room_num=row;//得到进入哪个房间
}

void dating::showEvent(QShowEvent *){
    //重新申请好友、房间、头像等信息
    ui->name_label->setText(local_user.name);
    room_num=-1;
    timer->start();
};


//刷新房间列表信息
void dating::show_room(){
    //将读取到的数据重新写回
    ;
}


//获得房间信息
void dating::read_room(){
    ;
}


