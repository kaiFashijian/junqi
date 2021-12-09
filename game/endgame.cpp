<<<<<<< HEAD
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
=======
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
>>>>>>> f09f4e0e1b1b4b7aa1b1d8390b52aef6cc169f3f
