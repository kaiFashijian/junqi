#include "information.h"
#include "ui_information.h"
#include "QIcon"
#include "QMessageBox"
#include "QFileDialog"
#include "QApplication"
#include "QPixmap"



Information::Information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
     this->setFixedSize(460,360);
    QIcon icon;
    icon.addFile(tr(":/back/img/11.png"));
    ui->pictureButton->setIcon(icon);
    ui->pictureButton->setIconSize(QSize(101,81));

    connect(ui->pictureButton,&QPushButton::clicked,[=](){
        QString fileName = QFileDialog::getOpenFileName(this,"选择文件",":/back/img","文本文件(*.png)");//获取文件名
        if(!fileName.isEmpty()){
//                    ui->lineEdit->setText(fileName);
//                    icon.addFile(fileName);
        QPixmap icon(fileName);
        ui->pictureButton->setIcon(icon);
        ui->pictureButton->setIconSize(QSize(101,81));
        } else {
            QMessageBox::warning(this,"打开文件","err: open file");
        }
    });
}

Information::~Information()
{
    delete ui;
}

void Information::on_upButton2_clicked()
{
    QMessageBox::information(this,"提示","提交成功");
    this->close();
}
