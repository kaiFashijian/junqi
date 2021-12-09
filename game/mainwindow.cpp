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

    this->ui->label_4->hide();
    this->ui->scrollArea->hide();

    this->setFixedSize(1380,1000);
    //设置窗口居中
    QDesktopWidget * desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    this->ui->centralwidget->findChild<QWidget *>("widget")->resize(750,941);



    QGridLayout *scrollAreaLayout = new QGridLayout() ;


    //向布局当中添加表情
    setEmoji(scrollAreaLayout);


    this->ui->scrollAreaWidgetContents->setLayout(scrollAreaLayout);


    float fRadio = 0.85;
    m_map = new QChessMap(QPoint(GAME_MAP_WIDTH, GAME_MAP_HEIGHT)*fRadio);
    m_map->setGeometry(10,100, 550, 800);
    this->layout()->addWidget(m_map);

    this->ui->scrollArea->raise();
    this->ui->scrollAreaWidgetContents->raise();

    //信号与槽关联
    connect(m_map,SIGNAL(MoveQi()), this, SLOT(SendMove()));
    connect(m_map,SIGNAL(QiTurn_map()),this,SLOT(SendTurn()));
    connect(this,SIGNAL(updateLabelForChess(QString)),m_map,SLOT(updateChess(QString)));
    connect(m_map,SIGNAL(updateLabel(QString)),this,SLOT(updateLabel(QString)));
    this->cont = Connection::getConnection();


    connect(this,SIGNAL(TurnFromOthers()),m_map,SLOT(OperateWithTurn()));
    connect(this,SIGNAL(MoveFromOthers()),m_map,SLOT(OperateWithMove()));

    //游戏在线发送消息
    connect(this->ui->pushButton_5, SIGNAL(clicked()), this, SLOT(SendTextLineInGame()));
    //表情
    connect(this->ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ShowEmojiArea()));


    this->w = new Message();
    connect(this->w,SIGNAL(reBootButton()),this,SLOT(setButton()));




//    //测试棋子情况显示
//    QImage *image = new QImage();
//    image->load(":/images/unfind.png");

//    this->ui->label_7->resize(100,100);
//    this->ui->label_7->setPixmap(QPixmap::fromImage(*image));

    initIconofChess();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SendMove()
{
    //向服务器发送棋子移动的坐标数据
    qDebug() << "sendMove";
    //myTurn = false;
    QString Command = "G&M"
            + QString::number(movePoint[0].x())
            + QString::number(movePoint[0].y())
            + QString::number(movePoint[1].x())
            + QString::number(movePoint[1].y());

    //发送棋子 判定是不是炸弹              ？？？？？
    QString mes = QString::number(movePoint[1].x()) + "&"
            + QString::number(movePoint[1].y());
    movePoint.clear();

    //qDebug() << "test1" << endl;
    //emit updateLabelForChess(mes);



    //sendMes(Command);
}

void MainWindow::SendTurn()
{
    qDebug() << "sendTurn";
    //myTurn = false;
    QString Command = "G&T"
            + QString::number(movePoint[0].x())
            + QString::number(movePoint[0].y());

    QString mes = QString::number(movePoint[0].x()) + "&"
            + QString::number(movePoint[0].y());

    movePoint.clear();
    //sendMes(Command);
    Connection *cont = Connection::getConnection();

    cont->sendMsg(Command);

    emit updateLabelForChess(mes);

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


    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    // SEND  MSG
    this->cont->sendMsg("G&W&" /*+ UID + "&"*/ + str + "#" + time);

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

//查看历史消息
void MainWindow::on_pushButton_4_clicked()
{
    this->w->show();
//    Message *w = new Message();
    this->ui->textEdit_2->setEnabled(false);
    this->ui->pushButton_3->setEnabled(false);
    this->ui->pushButton_5->setEnabled(false);

    this->ui->pushButton_4->setEnabled(false);



}

//游戏结束
void MainWindow::on_pushButton_2_clicked()
{
    this->cont->sendMsg("G&LOSE");
    //投降

    //弹出一个最后的终结框，告知输了，减掉积分，告知段位变化，询问加不加好友
    this->endGame = new Endgame();
    this->endGame->setWindowModality(Qt::ApplicationModal);
    this->endGame->show();

    //发送积分，段位变更

    this->cont->sendMsg("G&R&"); //+ )

}

void MainWindow::setButton()
{
    this->ui->pushButton_4->setEnabled(true);

    this->ui->textEdit_2->setEnabled(true);
    this->ui->pushButton_3->setEnabled(true);
    this->ui->pushButton_5->setEnabled(true);

}

//和网络流共用一个信号,默认红色阵营改变上方，蓝色阵营改变下方
void MainWindow::changeIconofChess(QString str)
{
    QStringList situation = str.split("&");

    QImage *turnOfChess = new QImage();
    QImage *deathOfChess = new QImage();

    turnOfChess->load(":/images/live.png");
    deathOfChess->load(":/images/unfind.png");

    if(situation[1] == "T")
        this->findChild<QLabel *>(str)->setPixmap(QPixmap::fromImage(*turnOfChess));
    else if(situation[1] == "M")
    {
        //if()
    }
}

void MainWindow::initIconofChess()
{
    QObjectList forLabel = this->ui->widget->children();

    QImage *image = new QImage();
    image->load(":/images/unfind.png");

    foreach (QObject *obj, forLabel) {
            if (obj->metaObject()->className() == QStringLiteral("QLabel")){
                QLabel *b = qobject_cast<QLabel*>(obj);
                if(b->text() == "TextLabel"){
                    b->setPixmap(QPixmap::fromImage(*image));
                    b->setAlignment(Qt::AlignCenter);
                }else if(b->text() != "null")
                {
                     mapForQiDisplay.insert(b->objectName(),getNumofChessType(b->objectName()));
                }
            }
        }


//    for(QMap<QString, int>::iterator it = mapForQiDisplay.begin();it != mapForQiDisplay.end();it++)
//          qDebug() << it.key();

}

int MainWindow::getNumofChessType(QString name)
{
    QStringList s = name.split("_");


    QString n;
    if(s.length() == 3)
        n = s[1] + "_" + s[2];
    else if(s.length() == 4)
        n = s[1] + "_" + s[2] + "_" + s[3];

    if(n == "CHESS_FALG" || n == "CHESS_Commande" || n == "CHESS_General")
    {
        return 1;
    }else if(n == "CHESS_BOMB" || n == "CHESS_Maj_general" || n == "CHESS_Brigadier" || n == "CHESS_Colonel" || n == "CHESS_Major")
    {
        return 2;
    }else if(n == "CHESS_MINE" || n == "CHESS_Captain" || n == "CHESS_Lieutenant" || n == "CHESS_Engineer")
    {
        return 3;
    }
}

void MainWindow::updateLabel(QString str)
{

    qDebug() << str;
    //接到了一个阵营_棋子类型的str
    QMap<QString, int>::iterator it;
    it = mapForQiDisplay.begin();
    while(it!=mapForQiDisplay.end())
    {
        if(it.key() == str)
        {
            int num = it.value();
            it.value() = num - 1;

            QString labelName = str + "_" + QString::number(num);
            qDebug() << labelName;
            QImage *Image = new QImage();
            Image->load(":/images/live.png");
            this->ui->widget->findChild<QLabel *>(labelName)
                       ->setPixmap(QPixmap::fromImage(*Image));

            break;
        }
        it++;
    }

}
