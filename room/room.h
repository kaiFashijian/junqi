#ifndef ROOM_H
#define ROOM_H

#include <QDialog>
#include "game/mainwindow.h"
#include <qtimer.h>
#include "public/connection.h"
#include "user/user.h"

namespace Ui {
class room;
}

class room : public QDialog
{
    Q_OBJECT

public:
    explicit room(QWidget *parent = nullptr);
    ~room();
    int ready_num=0;//1为测试时使用，实际应为0
    QTimer* timer;
    void showEvent(QShowEvent *);

private slots:
    void enter_game();

    //void on_exit_button_clicked();


private:
    Ui::room *ui;
    MainWindow game;

signals:
    void back();


};

#endif // ROOM_H
