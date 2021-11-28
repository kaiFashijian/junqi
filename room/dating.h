#ifndef DATING_H
#define DATING_H

#include <QDialog>
#include "qlistwidget.h"
#include "room.h"
#include <qmessagebox.h>
#include <QPushButton>

namespace Ui {
class dating;
}

class dating : public QDialog
{
    Q_OBJECT

public:
    explicit dating(QWidget *parent = nullptr);
    ~dating();
    int room_num=-1;

private slots:

    void on_roomtable_cellClicked(int row, int column);

private:
    room* room_a;
    Ui::dating *ui;
};

#endif // DATING_H
