/*
 *
 *  qchessmap用于本地的走棋逻辑判断
 *
 *  还需要增加鼠标事件--用于基本的棋子移动
 *
 * 注意原始给的坐标系统  x是指的是列数；
 *                    y指的是行数
 *
 * */

#ifndef QCHESSMAP_H
#define QCHESSMAP_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <algorithm>

#include "qchess.h"
#include "public/public.h"

class QChessMap : public QWidget
{
    Q_OBJECT

private:
    QPoint m_pSize;
    QPoint m_pChessSize;
    QLabel *m_lbBackground;
    QLabel *m_lbChessBoard;
    QVector<QChess*> m_chess;
    //显示棋子的占位情况
    int BarrackMap[12][5];
    //显示棋盘的铁路和公路分布
    int roadMap[12][5];
    //显示棋盘的棋子分布
    int QiMap[12][5];
    //用于dfs的矩阵
    int dfsMatrix[12][5];

public:
    explicit QChessMap(const QPoint &size, QWidget *parent = nullptr);

    //逻辑判断

    // 初始化棋盘图片，放置棋子
    void initMap();
    //单独提出来绘制棋子（保持两边的棋子位置一致，也要保证每次开游戏时棋子位置任意）
    void initQi();
    // 通过棋盘坐标获取坐标点,用于放置棋子位置
    QPoint GetChessPos(int nX, int nY);
    //剔除行营的位置
    bool IsBarracks(int nX, int nY);
    //捕捉鼠标事件
    void mousePressEvent(QMouseEvent *event);
    //撤销点击对象
    void unselect(int status);
    //检索路径dfs算法
    bool JudgePath(QChess *SourceChess);
    void dfs(bool flag, int Sx, int Sy, int Dx, int Dy);


    //服务器发送信息
public slots:
    void sendQiTurn();
    void sendMoveQi();
    void OperateWithTurn();
    void OperateWithMove();

signals:
    void QiTurn_map();
    void MoveQi();

};

#endif // QCHESSMAP_H
