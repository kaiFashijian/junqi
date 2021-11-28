#include "emoji.h"

Emoji::Emoji(int i)
{
    this->resize(35,35);
    this->setText(emojiStr[i]);
    this->myEmo = emojiStr[i];
}

void Emoji::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        qDebug() << "表情：  "<< this->myEmo;
        emit cuteClicked(this->myEmo);
    }
}

QString Emoji::getEmostr()
{
    return this->myEmo;
}
