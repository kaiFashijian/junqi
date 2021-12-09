#ifndef ENDGAME_H
#define ENDGAME_H

#include <QWidget>

namespace Ui {
class Endgame;
}

class Endgame : public QWidget
{
    Q_OBJECT

public:
    explicit Endgame(QWidget *parent = nullptr);
    ~Endgame();

private:
    Ui::Endgame *ui;

signals:
    void backTodating();
private slots:
    void on_pushButton_2_clicked();
};

#endif // ENDGAME_H
