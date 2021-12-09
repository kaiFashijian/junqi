<<<<<<< HEAD
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QGridLayout>
#include "qnchatmessage.h"
#include "public/connection.h"
#include "emoji.h"
#include "public/public.h"



namespace Ui {
class Message;
}

class Message : public QMainWindow
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = 0);
    ~Message();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);

    void setEmoji(QGridLayout *myLayOut);

    void keyPressEvent(QKeyEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void addEmojiTotheSentence(QString emo);

    void closeEvent(QCloseEvent *e);

    void WordsFromOther(QString str);

private:
    Ui::Message *ui;
    Connection *cont;

    QVector<Emoji *> vEmo;

signals:

    void reBootButton();


};

#endif // MAINWINDOW_H
=======
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QGridLayout>
#include "qnchatmessage.h"
#include "public/connection.h"
#include "emoji.h"
#include "public/public.h"



namespace Ui {
class Message;
}

class Message : public QMainWindow
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = 0);
    ~Message();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);

    void setEmoji(QGridLayout *myLayOut);

    void keyPressEvent(QKeyEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void addEmojiTotheSentence(QString emo);

    void closeEvent(QCloseEvent *e);

    void WordsFromOther(QString str);

private:
    Ui::Message *ui;
    Connection *cont;

    QVector<Emoji *> vEmo;

signals:

    void reBootButton();


};

#endif // MAINWINDOW_H
>>>>>>> f09f4e0e1b1b4b7aa1b1d8390b52aef6cc169f3f
