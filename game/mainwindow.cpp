#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QVBoxLayout>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //窗口大小
    this->setFixedSize(1500,1000);
    //设置窗口居中
    QDesktopWidget * desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    this->ui->label_4->hide();
    Emoji * e = new Emoji(3);

    e->show();
    QGridLayout *scrollAreaLayout = new QGridLayout() ;
//    scrollAreaLayout->setVerticalSpacing(15);
//    scrollAreaLayout->setHorizontalSpacing(10);

    //向布局当中添加表情
    setEmoji(scrollAreaLayout);


    this->ui->scrollAreaWidgetContents->setLayout(scrollAreaLayout);
    //this->ui->scrollArea->setWidget(this->ui->scrollAreaWidgetContents);

    //this->ui->scrollArea->hide();

    float fRadio = 0.85;
    m_map = new QChessMap(QPoint(GAME_MAP_WIDTH, GAME_MAP_HEIGHT)*fRadio);
    m_map->setGeometry(10,100, 550, 800);
    this->layout()->addWidget(m_map);

    //信号与槽关联
    connect(m_map,SIGNAL(MoveQi()), this, SLOT(SendMove()));
    connect(m_map,SIGNAL(QiTurn_map()),this,SLOT(SendTurn()));

    //connect(client,SIGNAL(readyRead()),this, SLOT(ReadMess()));
    Connection *cont = Connection::getConnection();
    connect(cont, SIGNAL(TestSignal), this, SLOT(ReadMess));

    connect(this,SIGNAL(TurnFromOthers()),m_map,SLOT(OperateWithTurn()));
    connect(this,SIGNAL(MoveFromOthers()),m_map,SLOT(OperateWithMove()));

    //游戏在线发送消息
    connect(this->ui->pushButton_5, SIGNAL(clicked()), this, SLOT(SendTextLineInGame()));
    //表情
    connect(this->ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ShowEmojiArea()));
    //ConnectServer();




    //debug 用
//     for(int i = 0;i < vEmo.size();i++)
//         qDebug() << vEmo[i]->getEmostr();
    //this->ui->label_6->setText("😊");
//    sendMes("U&R&1926385889@qq.com&123456");
//    this->emo = new Emoji();
//    emo->show();

    // debug 用


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SendMove()
{
    //向服务器发送棋子移动的坐标数据
    qDebug() << "sendMove";
    myTurn = false;
    QString Command = "G&M"
            + QString::number(movePoint[0].x())
            + QString::number(movePoint[0].y())
            + QString::number(movePoint[1].x())
            + QString::number(movePoint[1].y());

    movePoint.clear();

    //sendMes(Command);
}

void MainWindow::SendTurn()
{
    qDebug() << "sendTurn";
    myTurn = false;
    QString Command = "G&T"
            + QString::number(movePoint[0].x())
            + QString::number(movePoint[0].y());

    movePoint.clear();
    //sendMes(Command);
    Connection *cont = Connection::getConnection();

    cont->sendMsg(Command);
}

void MainWindow::ReadMess(QString str)
{
    qDebug() << str;

//    QString mes = readMes();
//    qDebug() << mes;

//    if(mes[0] == 'G')
//    {
//        if(mes[2] == 'T')
//        {
//            myTurn = true;
//            QString temp = mes.mid(3,1);
//            int turnx = temp.toInt();
//            temp = mes.mid(4,1);
//            int turny = temp.toInt();


//            TurnPoint.setX(turnx);
//            TurnPoint.setY(turny);

//            emit TurnFromOthers();
//        }

//        if(mes[2] == 'M')
//        {
//            myTurn = true;
//            int SourceX, SourceY, DesX, DesY;
//            QString temp = mes.mid(3,1);
//            SourceX = temp.toInt();
//            temp = mes.mid(4,1);
//            SourceY = temp.toInt();
//            temp = mes.mid(5,1);
//            DesX = temp.toInt();
//            temp = mes.mid(6,1);
//            DesY = temp.toInt();

//            MovePoint.push_back(QPoint(SourceX, SourceY));
//            MovePoint.push_back(QPoint(DesX, DesY));

//            emit MoveFromOthers();

//        }

//        //接受消息
//        if(mes[2] == 'W')
//        {
//           QStringList l = mes.split("&");
//           this->ui->label_3->setText(l[2]);
//        }
//    }

}

void MainWindow::SendTextLineInGame()
{
    QString str = this->ui->textEdit_2->toPlainText();
    if(str == NULL || str == "")
    {
        //新增一个提示
        qDebug() << "SendTextLineInGame 发送消息为空";
        this->ui->label_4->show();
        return ;
    }
    if(!this->ui->label_4->isHidden())
        this->ui->label_4->hide();

    qDebug() << "SendTextLineInGame  " << str;

    //还需要加上对战玩家的uid和特殊的指令格式
    //sendMes(str);

    this->ui->textEdit_2->setText("");
}

void MainWindow::ShowEmojiArea()
{
    if(this->ui->scrollArea->isHidden())
    {
        this->ui->scrollArea->show();
    }
    else
        this->ui->scrollArea->hide();
}

//添加表情
void MainWindow::setEmoji(QGridLayout *myLayOut)
{
    int num = emojiStr.size();
    int row = 0; int colunm = 0;
    for(int i = 0;i < num;i++)
    {
        Emoji *e = new Emoji(i);
        connect(e, SIGNAL(cuteClicked(QString)), this, SLOT(addEmojiTotheSentence(QString)));
        myLayOut->addWidget(e,row,colunm,1,1);
        vEmo.push_back(e);
        colunm++;
        if(colunm > 9)
        {
            row++;
            colunm = 0;
        }
    }
}

void MainWindow::addEmojiTotheSentence(QString str)
{
    QString senEmo = this->ui->textEdit_2->toPlainText();
    senEmo += str;
    this->ui->textEdit_2->setText(senEmo);
    qDebug() << "add:   " << senEmo;
}
/*
 * 好友功能 存uid
 *
 * 每一个channel都用uid标识
 *
 * 加入房间 获取对方信息
 * 创建房间的时候，发送B&房间号
 * 数据库表存房间号，人数，房主的信息，加入人的信息
 * 有人加入用uid找人，发送基本信息
 * 本地存储一个对局玩家的uid
 * 发送信息带uid
 *
 * 退出还得给服务器一个uid+信息
 *
 * 1. 用户模块
 * U&L&邮箱&密码   返回U&S&uid&头像&...   返回U&W
 * U&R&邮箱&密码    返回U&S U&W
 * U&M&邮箱&密码     返回U&S U&W
 *
 * 2.辅助模块
 * S&U&UID&昵称
 *
 * 3.房间模块
 *
 * R&N 需要服务器传现有的房间信息       R&N&“房间号+人数”一堆，中间以&间隔
 * R&C&房间号&房主UID   服务器广播一次   R&N&“房间号+人数”一堆，中间以&间隔
 * R&J&房间号&玩家UID   服务器广播一次   R&N&“房间号+人数”一堆，中间以&间隔
 *
 * R&O                       R&O&对方是否已准备（1是准备了，0是没准备）
 *
 *
 * */
