#include "message.h"
#include "ui_message.h"
#include <QDateTime>
#include <QDebug>

Message::Message(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);

    resize(600, 800);

    this->cont = Connection::getConnection();
    this->ui->scrollArea->hide();

    QGridLayout *grid = new QGridLayout();
    setEmoji(grid);

    this->ui->scrollAreaWidgetContents_2->setLayout(grid);


    connect(this->cont, SIGNAL(WordsInGame(QString)), this, SLOT(WordsFromOther(QString)));

}

Message::~Message()
{
    delete ui;
}

void Message::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳


    //发送到服务端 对方用户uid
    this->cont->sendMsg("G&W&1212&" + msg + "#" + time);


    bool isSending = true; // 发送中7

    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();


    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void Message::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void Message::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void Message::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

void Message::on_pushButton_2_clicked()
{
    //产生表情

    if(this->ui->scrollArea->isHidden())
    {
        this->ui->scrollArea->show();
    }
    else
        this->ui->scrollArea->hide();
}


void Message::setEmoji(QGridLayout *myLayOut)
{
    int num = emojiStr.size();
    int row = 0; int colunm = 0;
    for(int i = 0;i < num;i++)
    {
        Emoji *e = new Emoji(i);
        connect(e, SIGNAL(cuteClicked(QString)), this, SLOT(addEmojiTotheSentence(QString)));
        myLayOut->addWidget(e,row,colunm,1,1);
        vEmo.push_back(e);
        colunm++;
        if(colunm > 9)
        {
            row++;
            colunm = 0;
        }
    }
}


void Message::addEmojiTotheSentence(QString emo)
{
    QString editstr = this->ui->textEdit->toPlainText();

    editstr += emo;

    this->ui->textEdit->setText(editstr);
}

void Message::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        on_pushButton_clicked();
    }
}

void Message::closeEvent(QCloseEvent *event)
{
    emit reBootButton();
}


void Message::WordsFromOther(QString str)
{

    QStringList data = str.split("#");

    QString time;
    QString text;

    time = data[1];
    text = data[0];


    bool isSending = true;

    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, text, time, QNChatMessage::User_She);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == text) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, text, time, QNChatMessage::User_She);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(text != "") {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, text, time, QNChatMessage::User_She);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}
