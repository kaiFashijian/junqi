#ifndef EMOJI_H
#define EMOJI_H

#include "public/public.h"

#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QDebug>


class Emoji : public QPushButton
{
    Q_OBJECT
public:
    Emoji(int i);
    void mousePressEvent(QMouseEvent * ev);
    QString getEmostr();
private:
    QString myEmo;
signals:
    void cuteClicked(QString str);
};

#endif // EMOJI_H
