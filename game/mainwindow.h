/*
 * 主窗口，用于接受信号并且发送相关信息，处理有关的信息并且向下传导
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "public/public.h"
#include "qchessmap.h"
#include "emoji.h"
#include "public/connection.h"


#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>

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

private:
    Ui::MainWindow *ui;
    QChessMap *m_map;
    QVector<Emoji *> vEmo;
    //Emoji *emo;


public slots:
    void SendTurn();
    void SendMove();
    void ReadMess(QString str);

    //发送游戏内的玩家交流
    void SendTextLineInGame();
    //表情
    void ShowEmojiArea();
    void addEmojiTotheSentence(QString);
signals:
    void TurnFromOthers();
    void MoveFromOthers();
};
#endif // MAINWINDOW_H
