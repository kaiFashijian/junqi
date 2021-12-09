#include "dating.h"
#include "ui_dating.h"



dating::dating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dating)
{
    ui->setupUi(this);
    room_a = new room(this);

    // 初始化与服务器的连接
    Connection *cont = Connection::getConnection();

    //向服务器要求房间信息
    QString str = "R&N";
    str.append(local_user.uid);
    cont->sendMsg(str);


    //初始化定时器
    timer=new QTimer();
    timer->start(5000);

    //选择房间
    //函数不会写，在下面

    //加入房间请求
    connect(ui->join_button, &QPushButton::clicked, room_a, [=](){
        if(room_num==-1||room_num>room_max){
             QMessageBox::information(NULL, "", "请先选择房间");
             //return;
        }
        else{
             QStringList temp_arr=room_arr[room_num].split('*');
             if( temp_arr[1]=='2'){
                 QMessageBox::information(NULL, "", "房间已满，加入失败");
                 return;
             }
             else{
                 //传值给服务器，告知服务器进入哪个房间，房间号为room_num
                 room_id=room_arr[0]+"的房间";
                 QString strJ="R&J";
                 //房间号、玩家名字、玩家uid
                 strJ.append(room_id).append("&").append(local_user.name).append("&").append(local_user.uid);
                 cont->sendMsg(strJ);
             }
            //服务器判断后如果可以返回R&J&S，否则为R&J&W

             //test
//             QMessageBox::information(NULL, "", "加入房间成功");
//             this->hide();
//             room_a->show();
//             room_a->room_id=this->room_id;  //传roomid
//             room_a->is_owner=1;
        }
    });


    //创建房间
    connect(ui->create_button,&QPushButton::clicked,room_a, [=](){
        //向服务器提出创建申请，向服务器发送房间号、房主名称和UID，应该会返回房间号
        QString strC="R&C&";
        strC.append(local_user.name+"的房间").append("&").append(local_user.name).append("&").append(local_user.uid);
        cont->sendMsg(strC);
        //创造成功的话，服务器将返回R&C&S

        //test
//        QMessageBox::information(NULL, "", "创建房间成功");
//        room_a->is_owner=0;
//        room_a->room_id=local_user.name+"的房间";
//        this->hide();
//        room_a->show();
    });


    //显示大厅列表
    //connect(timer,SIGNAL(timeout()),this,SLOT(show_room()));  //主动发的话那不用刷新请求了
    connect(cont, &Connection::RNsignal, this,&dating::read_room);

    //显示头像，昵称，积分
    //在showevent内

    //创建房间成功
    connect(cont, &Connection::RCSsignal, this,[=](){
        QMessageBox::information(NULL, "", "创建房间成功");
        room_a->is_owner=0;
        room_a->room_id=local_user.name+"的房间";
        this->hide();
        room_a->show();
    });

    //创建房间失败，可能用不到，先写了
    connect(cont, &Connection::RCWsignal, this,[=](){
        QMessageBox::information(NULL, "", "创建房间失败");
    });

    //加入房间成功
    connect(cont, &Connection::RJSsignal, this,[=](){
        QMessageBox::information(NULL, "", "加入房间成功");
        this->hide();
        room_a->show();
        room_a->room_id=this->room_id;  //传roomid
        room_a->is_owner=1;
    });

    //加入房间失败
    connect(cont, &Connection::RJWsignal, this,[=](){
            QMessageBox::information(NULL, "", "加入房间失败");
        });

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
    ui->score_label->setText(QString::number(local_user.scores));
    //头像还没弄
    //local_user.friends_list<<"1"<<"2";  //test
    ui->friendlist->addItems(local_user.friends_list);
    room_num=-1;
    timer->start();


    read_room("one*1#two*2"); //test

};


//每4秒刷新房间列表信息
void dating::show_room(){
     //QMessageBox::information(NULL, "", "刷新");
    //向服务器要求房间信息
    QString str = "R&N";
    str.append(local_user.uid);
    Connection *cont = Connection::getConnection();
    cont->sendMsg(str);
}


//获得房间信息
void dating::read_room(QString msg){
    room_arr.clear(); //清空房间缓存
    room_arr = msg.split('#');  //好几组 名字*人数
    int j=0;//第一行
    //QStringList room_arr;
    //room_arr<<"one*1"<<"two*2";  //test
    int max=room_arr.size();
    room_max=max;
    for(int i=0;i<max;i++){
        QStringList temp_arr=room_arr[i].split('*');
        ui->roomtable->setItem(j,0,new QTableWidgetItem(temp_arr[0]+"的房间"));
        ui->roomtable->setItem(j,1,new QTableWidgetItem(temp_arr[1]+"/2"));
        j++;
    }
}



