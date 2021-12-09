<<<<<<< HEAD
/*
 * 主窗口，用于接受信号并且发送相关信息，处理有关的信息并且向下传导
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "public/public.h"
#include "qchessmap.h"
#include "emoji.h"
#include "public/connection.h"
#include "message.h"
#include "endgame.h"


#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QDateTime>
#include <QPixmap>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //表情添加
    void setEmoji(QGridLayout *myLayOut);

    //publc 变量 另一个玩家的信息，自己的积分，头像等等等
//    void sendResult();

    void changeIconofChess(QString str);
    void initIconofChess();
    int getNumofChessType(QString name);

private:
    Ui::MainWindow *ui;
    QChessMap *m_map;
    QVector<Emoji *> vEmo;
    //Emoji *emo;
    Connection *cont;
    Endgame *endGame;

    Message *w;

public slots:
    void SendTurn();
    void SendMove();

    //发送游戏内的玩家交流
    void SendTextLineInGame();
    //表情
    void ShowEmojiArea();
    void addEmojiTotheSentence(QString);

    void setButton();
signals:
    void TurnFromOthers();
    void MoveFromOthers();

    void updateLabelForChess(QString);
private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();

    void updateLabel(QString str);
};
#endif // MAINWINDOW_H
=======
/*
 * 主窗口，用于接受信号并且发送相关信息，处理有关的信息并且向下传导
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "public/public.h"
#include "qchessmap.h"
#include "emoji.h"
#include "public/connection.h"
#include "message.h"
#include "endgame.h"


#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QDateTime>
#include <QPixmap>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //表情添加
    void setEmoji(QGridLayout *myLayOut);

    //publc 变量 另一个玩家的信息，自己的积分，头像等等等
//    void sendResult();

    void changeIconofChess(QString str);
    void initIconofChess();
    int getNumofChessType(QString name);

private:
    Ui::MainWindow *ui;
    QChessMap *m_map;
    QVector<Emoji *> vEmo;
    //Emoji *emo;
    Connection *cont;
    Endgame *endGame;

    Message *w;

public slots:
    void SendTurn();
    void SendMove();

    //发送游戏内的玩家交流
    void SendTextLineInGame();
    //表情
    void ShowEmojiArea();
    void addEmojiTotheSentence(QString);

    void setButton();
signals:
    void TurnFromOthers();
    void MoveFromOthers();

    void updateLabelForChess(QString);
private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();

    void updateLabel(QString str);
};
#endif // MAINWINDOW_H
>>>>>>> f09f4e0e1b1b4b7aa1b1d8390b52aef6cc169f3f
