/*
 *
 * qchess类代表棋盘上的每一个按钮控件
 *
 *
 */

#ifndef QCHESS_H
#define QCHESS_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

#include "public/public.h"
class QChess : public QPushButton
{
    Q_OBJECT
private:
    CAMP_TYPE m_camp;   // 阵营
    CHESS_TYPE m_type;  // 棋子级别

    bool m_bShown;      // 是否被翻开
    bool m_bSelect;     //翻转后再次点击被选中

    //新增棋子的位置
    int posx;
    int posy;

public:
    explicit QChess(CAMP_TYPE camp, CHESS_TYPE type, int forx, int fory,QWidget *parent = nullptr);
    void SetChessType(CAMP_TYPE camp, CHESS_TYPE type);
    void updatePic();
    //点击事件
    void OnClick();
    //重写点击事件
    void mousePressEvent(QMouseEvent *event);

    //get函数得到坐标
    int getPosx();
    int getPosy();

    void setPosx(int newX);
    void setPosy(int newY);

    //得到阵营
    CAMP_TYPE getCamp();
    //得到类型
    CHESS_TYPE getType();

    void setSelect(bool flag);
    void setShow(bool flag);



signals:
    void QiTurn();
    void moveButton();

};

#endif // QCHESS_H
