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

    // 点击头像图片按钮后打开文件浏览器挑选图片
    connect(ui->pictureButton,&QPushButton::clicked,[=](){
        /* TODO(@yin@li@ye)
         *      本地选择图片
         *          |
         *       上传图床
         *          |
         *    保存图床返回的url------->修改local_user
         *          |
         *   传递新的url给服务器
         *          |
         *  服务器返回修改成功信息
         *          |
         *   根据新的url下载图片------->保存在哪里？
         *          |
         *    展示图片给用户看
         */

        QString fileName = QFileDialog::getOpenFileName(this,"选择文件",":/back/img","文本文件(*.png)");//获取文件名
        if(!fileName.isEmpty()){
//          ui->lineEdit->setText(fileName);
//          icon.addFile(fileName);
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
