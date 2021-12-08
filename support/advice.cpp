#include "advice.h"
#include "ui_advice.h"
#include "QMessageBox"

Advice::Advice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Advice)
{
    ui->setupUi(this);
    this->setFixedSize(540,380);
}

Advice::~Advice()
{
    delete ui;
}

void Advice::on_upButton_clicked()
{
    QMessageBox::information(this,"提示","反馈成功");
    this->close();
}
