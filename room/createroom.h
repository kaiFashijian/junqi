#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QDialog>
#include"room.h"

namespace Ui {
class createRoom;
}

class createRoom : public QDialog
{
    Q_OBJECT

public:
    explicit createRoom(QWidget *parent = nullptr);
    ~createRoom();

private:
    Ui::createRoom *ui;
    room* room_a;
};

#endif // CREATEROOM_H
