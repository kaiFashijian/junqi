<<<<<<< HEAD
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
=======
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
>>>>>>> f09f4e0e1b1b4b7aa1b1d8390b52aef6cc169f3f
