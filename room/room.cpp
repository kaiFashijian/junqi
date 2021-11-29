#include "room.h"
#include "ui_room.h"

room::room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::room)
{
    ui->setupUi(this);
}

room::~room()
{
    delete ui;
}

//退出房间
void room::on_pushButton_clicked()
{

    this->close();
}

//准备游戏
void room::on_pushButton_2_clicked()
{
    ui->label_6->setText("         已准备");
}
