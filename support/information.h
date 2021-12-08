#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Information;
}

class Information : public QDialog {
    Q_OBJECT

public:
    explicit Information(QWidget *parent = 0);
    ~Information();

private slots:
    void on_upButton2_clicked();

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
