#include "endgame.h"
#include "ui_endgame.h"

Endgame::Endgame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Endgame)
{
    ui->setupUi(this);
}

Endgame::~Endgame()
{
    delete ui;
}

void Endgame::on_pushButton_2_clicked()
{
    emit backTodating();
}
