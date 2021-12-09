#ifndef ADVICE_H
#define ADVICE_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Advice;
}

class Advice : public QDialog
{
    Q_OBJECT

public:
    explicit Advice(QWidget *parent = 0);
    ~Advice();

private slots:
   void on_upButton_clicked();

private:
    Ui::Advice *ui;
};

#endif // ADVICE_H
