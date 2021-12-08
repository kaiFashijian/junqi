#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "advice.h"
#include <QMenuBar>
#include<QDebug>
#include "information.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
//    创建开始菜单
    QMenu * advicebutton=bar->addMenu("辅助功能");

    //    创建功能
    QAction * quitAction =advicebutton->addAction("用户反馈");
    connect(quitAction,&QAction::triggered,[=](){

        Advice *pic=new Advice();//初始化界面
        pic->show();
    });
    QAction * informationchange =advicebutton->addAction("信息修改");
    connect(informationchange,&QAction::triggered,[=](){

        Information *pic1=new Information();
        pic1->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::adviceopen()
//{
//    this->close();



//}
