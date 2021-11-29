#include "dating.h"
#include "ui_dating.h"



dating::dating(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dating)
{
    ui->setupUi(this);
    this->a1 = new room();

    connect(ui->pushButton, &QPushButton::clicked, a1, [=](){
        this->hide();
        a1->show();
    });

}

dating::~dating()
{
    delete ui;
}


/*
void dating::on_tableWidget_cellActivated(int row, int column)
{
    room_num=column;//得到进入哪个房间
}

void dating::on_pushButton_clicked()
{
//if(room_num!=-1)
    //此处应该传值给服务器
    a1=new room;
    a1->open();


}
*/

