#include "qchessmap.h"

QChessMap::QChessMap(const QPoint &size, QWidget *parent) :
    QWidget(parent),
    m_pSize(size)
{

    m_pChessSize.ry() = GAME_CELL_HEIGHT * (1.0*size.y() / GAME_MAP_HEIGHT);
    m_pChessSize.rx() = GAME_CELL_WIDTH * (1.0*size.x() / GAME_MAP_WIDTH);

    //初始化矩阵map

    // 1为该位置上有行营\有棋子
    for(int i = 0;i < 12;i++)
    {
        for(int j = 0;j < 5;j++)
        {
            QiMap[i][j] = 1;
            BarrackMap[i][j] = 0;
        }
    }

    BarrackMap[2][1] = 1;
    QiMap[2][1] = 0;

    BarrackMap[2][3] = 1;
    QiMap[2][3] = 0;

    BarrackMap[4][1] = 1;
    QiMap[4][1] = 0;

    BarrackMap[4][3] = 1;
    QiMap[4][3] = 0;

    BarrackMap[7][1] = 1;
    QiMap[7][1] = 0;

    BarrackMap[7][3] = 1;
    QiMap[7][3] = 0;

    BarrackMap[9][1] = 1;
    QiMap[9][1] = 0;

    BarrackMap[9][3] = 1;
    QiMap[9][3] = 0;

    BarrackMap[3][2] = 1;
    QiMap[3][2] = 0;

    BarrackMap[8][2] = 1;
    QiMap[8][2] = 0;
    // 1为在铁路上
    for(int i = 0;i < 5;i++)
    {
        roadMap[5][i] = 1;
        roadMap[1][i] = 1;
        roadMap[6][i] = 1;
        roadMap[10][i] = 1;
    }

    for(int i = 1;i < 11;i++)
    {
        roadMap[i][0] = 1;
        roadMap[i][4] = 1;
    }

    for(int i = 0;i < 12;i++)
    {
        for(int j = 0;j < 5;j++)
        {
            dfsMatrix[i][j] = 0;
        }
    }
    initMap();

}


void QChessMap::initMap()
{
    m_lbBackground = new QLabel(this);
    m_lbBackground->setGeometry(0, 0, m_pSize.x(), m_pSize.y());

    // 添加棋盘图片
    QImage *img = new QImage();
    img->load(":/images/chess_board.png");

    QImage imgSacle = img->scaled(m_pSize.x(),m_pSize.y(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_lbBackground->setPixmap(QPixmap::fromImage(imgSacle));

    this->initQi();
}


void QChessMap::initQi()
{
    // 添加棋子图片
    // 初始化剩余棋子位置记录
    QVector<QPoint> posRest;
    for(int x = 0; x < 5;x++){
        for(int y = 0; y<12;y++){
            if(!IsBarracks(x, y))
                posRest.push_back(QPoint(x,y));
        }
    }

    m_chess.clear();
        for(int type = CHESS_FALG; type<= CHESS_Engineer; type++){
            for(int camp = RED;camp<=BLUE;camp++){
                for(int n = 0; n < GetChessTypeNum((CHESS_TYPE)type); n++){

                    //使用srand函数初始化seed,实现随机排列  服务器给吧
                    srand(seed);

                    int nIndex = rand() % posRest.count();

                    QPoint pos = GetChessPos(posRest[nIndex].x(), posRest[nIndex].y());
                    //新增记录棋子位置的变量
                    QChess *chess = new QChess((CAMP_TYPE)camp, (CHESS_TYPE)type, posRest[nIndex].x(), posRest[nIndex].y(), this);

                    connect(chess,SIGNAL(QiTurn()),this,SLOT(sendQiTurn()));
                    connect(chess,SIGNAL(moveButton()),this,SLOT(sendMoveQi()));



                    chess->setEnabled(true);

                    chess->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());
                    posRest.remove(nIndex);
                    m_chess.push_back(chess);
                }
            }
        }
}


QPoint QChessMap::GetChessPos(int nX, int nY)
{
    QPoint pos = QPoint(0,0);
    float fXRadio, fYRadio;

    fXRadio = m_pSize.x()*1.0 / GAME_MAP_WIDTH;
    fYRadio = m_pSize.y()*1.0 / GAME_MAP_HEIGHT;

    if(nX < 0 || nX > 4 || nY<0|| nY>11){
        return pos;
    }

    pos.rx() = (GAME_UP_WIDTH + (nX*(GAME_CELL_WIDTH + GAME_OFF_WIDTH))) * fXRadio;

    if(nY<=5){
        pos.ry() = (GAME_UP_HEIGHT + (nY*(GAME_CELL_HEIGHT + GAME_OFF_HEIGHT))) * fYRadio;
    }else{
        pos.ry() = (GAME_DOWN_HEIGHT + (nY-6)*(GAME_CELL_HEIGHT + GAME_OFF_HEIGHT)) * fYRadio;
    }
    return pos;
}

bool QChessMap::IsBarracks(int nX, int nY)
{
    qDebug() <<"IsBarracks判断行营：" <<nX << nY;
    if((nX == 1 && nY == 2)
       || (nX == 1 && nY == 4)
       || (nX == 2 && nY == 3)
       || (nX == 3 && nY == 2)
       || (nX == 3 && nY == 4)
       || (nX == 1 && nY == 7)
        || (nX == 1 && nY == 9)
        || (nX == 2 && nY == 8)
        || (nX == 3 && nY == 7)
        || (nX == 3 && nY == 9)){
        return true;
    }
    return  false;
}

void QChessMap::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "鼠标点击确定路径";
    if(event->button() == Qt::LeftButton)
    {
        QPoint posion;

        int column = (event->pos().x() - 30)/110;
        int row = (event->pos().y() - 50)/50;
        if(event->pos().x() - column * 105 - 30 <= 85){
            qDebug()<<"列数："<<column;
        }else return ;

        if(event->pos().y() - row * 50 - 50 <= 40){
            qDebug()<<"行数："<<row;
        }else return;

        posion.setY(row);
        posion.setX(column);

        if(movePoint.size() == 1)
        {

            int tempx1 = movePoint[0].x();
            int tempy1 = movePoint[0].y();

            QChess *tempChess1;

            for(int i = 0;i < m_chess.size();i++)
            {
                if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
                    tempChess1 = m_chess[i];
            }
            movePoint.push_back(posion);
            //直接调用dfs() 检查路径 能走，触发信号
            if(JudgePath(tempChess1))
            {
                //更新棋盘信息
                QiMap[row][column] = 1;
                QiMap[tempChess1->getPosy()][tempChess1->getPosx()] = 0;

                tempChess1->setPosx(column);
                tempChess1->setPosy(row);
                qDebug() << "new pos" << tempChess1->getPosx() << "   " << tempChess1->getPosy();
                QPoint pos = GetChessPos(tempChess1->getPosx(), tempChess1->getPosy());
                tempChess1->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());

                tempChess1->setSelect(false);
                tempChess1->updatePic();

                emit MoveQi();
            }
            else
            {
                qDebug() << "错误：路径不允许";
                unselect(2);
                return ;
            }

        }
        else
        {
            return ;
        }
    }
}


void QChessMap::unselect(int status)
{
    if(status == 1)
    {
        //吃子

        int tempx1 = movePoint[0].x();
        int tempy1 = movePoint[0].y();
        int tempx2 = movePoint[1].x();
        int tempy2 = movePoint[1].y();

        QChess *tempChess1;
        QChess *tempChess2;



        for(int i = 0;i < m_chess.size();i++)
        {
            if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
                tempChess1 = m_chess[i];
            if(m_chess[i]->getPosx() == tempx2 && m_chess[i]->getPosy() == tempy2)
                tempChess2 = m_chess[i];
        }
//             qDebug() << tempChess1->getPosx() << tempChess1->getPosy();
        tempChess1->setSelect(false);
        tempChess1->updatePic();

        tempChess2->setSelect(false);
        tempChess2->updatePic();

        movePoint.clear();

    }
    if(status == 2)
    {
        if(movePoint.size() == 0)
            return ;

        //点击空位置
        int tempx1 = movePoint[0].x();
        int tempy1 = movePoint[0].y();

        QChess *tempChess1;
        for(int i = 0;i < m_chess.size();i++)
        {
            if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
                tempChess1 = dynamic_cast<QChess *>(m_chess[i]);
        }

        tempChess1->setSelect(false);
        tempChess1->updatePic();

        movePoint.clear();
    }
}

void QChessMap::dfs(bool flag, int Sx, int Sy, int Dx, int Dy)
{
    if(Sx == Dx && Sy == Dy)
    {
        flag = true;
        return ;
    }

    //四个方向且判断没有超，没有重复走
    if(!dfsMatrix[Sx][Sy+1] && roadMap[Sx][Sy+1] == 1 && Sy+1 < 5)
    {
        dfsMatrix[Sx][Sy+1] = 1;
        dfs(flag,Sx,Sy+1,Dx,Dy);
        dfsMatrix[Sx][Sy+1] = 0;
    }
    if(!dfsMatrix[Sx][Sy-1] && roadMap[Sx][Sy-1] == 1 && Sy-1 >= 0)
    {
        dfsMatrix[Sx][Sy-1] = 1;
        dfs(flag,Sx,Sy-1,Dx,Dy);
        dfsMatrix[Sx][Sy-1] = 0;
    }
    if(!dfsMatrix[Sx+1][Sy] && roadMap[Sx+1][Sy] == 1 && Sx+1 < 12)
    {
        dfsMatrix[Sx+1][Sy] = 1;
        dfs(flag,Sx+1,Sy,Dx,Dy);
        dfsMatrix[Sx+1][Sy] = 0;
    }
    if(!dfsMatrix[Sx-1][Sy] && roadMap[Sx-1][Sy] == 1 && Sx-1 >= 0)
    {
        dfsMatrix[Sx-1][Sy] = 1;
        dfs(flag,Sx-1,Sy,Dx,Dy);
        dfsMatrix[Sx-1][Sy] = 0;
    }

    return ;
}

//判断能不能走到那个位置
 bool QChessMap::JudgePath(QChess *SourceChess)
{
    //工兵特判
    int SourceMapX = movePoint[0].y();
    int SourceMapY = movePoint[0].x();

    int DesMapX = movePoint[1].y();
    int DesMapY = movePoint[1].x();

    qDebug() << "判断源路径：" << SourceMapX << "  " << SourceMapY;
    qDebug() << "判断目的路径：" << DesMapX << "  " << DesMapY;

    int distance = abs(SourceMapX - DesMapX) + abs(SourceMapY - DesMapY);

    if(roadMap[SourceMapX][SourceMapY] && roadMap[DesMapX][DesMapY])
    {
        //深度dfs(); 两个坐标都在铁路上面，特判工兵
        if(SourceChess->getType() == 12)
        {
            bool flag = false;
            dfsMatrix[SourceMapX][SourceMapY] = 1;
            dfs(flag, SourceMapX, SourceMapY, DesMapX, DesMapY);

            if(flag) return true;
            else return false;
        }
        else
        {
            if(SourceMapX == DesMapX)
            {
                for(int i = qMin(SourceMapY,DesMapY) + 1;i < qMax(SourceMapY,DesMapY);i++)
                    if(QiMap[SourceMapX][i] == 1)
                        return false;

                return true;
            }
            else if(SourceMapY == DesMapY)
            {
                for(int i = qMin(SourceMapX,DesMapX) + 1;i < qMax(SourceMapX,DesMapX);i++)
                    if(QiMap[i][SourceMapY] == 1)
                        return false;

                return true;
            }
            else return false;
        }
    }
    else
    {
        if(distance == 1)
            return true;
        if(distance == 2)
        {
            if(BarrackMap[SourceMapX][SourceMapY] == 1 || BarrackMap[DesMapX][DesMapY] == 1)
            {
                if(abs(SourceMapX - DesMapX) == 1 && abs(SourceMapY - DesMapY) == 1)
                    return true;
                else return false;
            }

            else return false;
        }
        else return false;
    }
}

void QChessMap::sendQiTurn()
{
    //mainwindow接受并发送
    emit QiTurn_map();
}


void QChessMap::sendMoveQi()
{
    //需要判断棋子能否移动了
    /*
        1. 同阵营的棋子不能吃
        2. 行营内的棋子不能吃
        3. 比他级别小的棋子不能吃
        4. 如果你不是工兵，那地雷和军旗你吃不了


        5. 点击的道路不通，也不能走

    */
    qDebug() << "吃子逻辑";
    int tempx1 = movePoint[0].x();
    int tempy1 = movePoint[0].y();
    int tempx2 = movePoint[1].x();
    int tempy2 = movePoint[1].y();

    qDebug() << "sendMoveQi" << tempx1 << tempy1 << tempx2 << tempy2;

    //一样要判断路径

    QChess *tempChess1;
    QChess *tempChess2;

    for(int i = 0;i < m_chess.size();i++)
    {
        if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
            tempChess1 = m_chess[i];
        if(m_chess[i]->getPosx() == tempx2 && m_chess[i]->getPosy() == tempy2)
            tempChess2 = m_chess[i];
    }

    //行营内
    qDebug() << tempChess1->getPosx() << tempChess1->getPosy() << tempChess1->getCamp();
    qDebug() << tempChess2->getPosx() << tempChess2->getPosy() << tempChess2->getCamp();


    if(IsBarracks(movePoint[1].x(),movePoint[1].y()))
    {
        qDebug() << "行营内";
        //消除两个棋子的按下状态，清空movepoint
        unselect(1);
        return ;
    }


    if(tempChess1->getCamp() == tempChess2->getCamp())
    {
        qDebug() << "同阵营" << tempChess1->getCamp() << "  " << tempChess2->getCamp();
        unselect(1);
        return ;
    }

    if(tempChess2->getType() == 1 || tempChess2->getType() == 2)
    {

        if(tempChess1->getType() != 12)
        {
            qDebug() << "军旗和地雷 非工兵";
            unselect(1);
            return ;
        }
    }

    if(tempChess1->getType() <= tempChess2->getType())
    {
        qDebug() << "级别不够";
        unselect(1);
        return ;
    }


    //吃子逻辑成功，需要重新创建一个按钮  更新地图信息

    for(QVector<QChess*>::iterator it = m_chess.begin();it != m_chess.end();it++)
    {
        if(*it == tempChess2)
        {
            m_chess.erase(it);
            break;
        }
    }

    qDebug() << "吃子逻辑判断成功";
    tempChess2->hide();

    QiMap[tempx1][tempy1] = 0;
    tempChess1->setPosx(tempChess2->getPosx());
    tempChess1->setPosy(tempChess2->getPosy());

    QPoint pos = GetChessPos(tempChess1->getPosx(), tempChess1->getPosy());
    tempChess1->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());

    //上传
    emit MoveQi();

    //

    movePoint.clear();
    return ;
}


void QChessMap::OperateWithTurn()
{
    QChess *tempChess1;
    for(int i = 0;i < m_chess.size();i++)
    {
        if(m_chess[i]->getPosx() == TurnPoint.x() && m_chess[i]->getPosy() == TurnPoint.y())
            tempChess1 = m_chess[i];
    }
    tempChess1->setShow(true);
    tempChess1->updatePic();
}

void QChessMap::OperateWithMove()
{

    int tempx1 = MovePoint[0].x();
    int tempy1 = MovePoint[0].y();
    int tempx2 = MovePoint[1].x();
    int tempy2 = MovePoint[1].y();

    qDebug() << "对局方移动" << tempx1 << tempy1 << tempx2 << tempy2;

    if(QiMap[tempy2][tempx2] == 1)
    {

        QChess *tempChess1;
        QChess *tempChess2;

        for(int i = 0;i < m_chess.size();i++)
        {
            if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
                tempChess1 = m_chess[i];
            if(m_chess[i]->getPosx() == tempx2 && m_chess[i]->getPosy() == tempy2)
                tempChess2 = m_chess[i];
        }

        for(QVector<QChess*>::iterator it = m_chess.begin();it != m_chess.end();it++)
        {
            if(*it == tempChess2)
            {
                m_chess.erase(it);
                break;
            }
        }

        tempChess2->hide();
        QiMap[tempx1][tempy1] = 0;
        tempChess1->setPosx(tempChess2->getPosx());
        tempChess1->setPosy(tempChess2->getPosy());

        QPoint pos = GetChessPos(tempChess1->getPosx(), tempChess1->getPosy());
        tempChess1->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());


    }
    else
    {
        QChess *tempChess1;
        for(int i = 0;i < m_chess.size();i++)
        {
            if(m_chess[i]->getPosx() == tempx1 && m_chess[i]->getPosy() == tempy1)
                tempChess1 = m_chess[i];
        }

        QiMap[tempy2][tempx2] = 1;
        QiMap[tempChess1->getPosy()][tempChess1->getPosx()] = 0;

        tempChess1->setPosx(tempx2);
        tempChess1->setPosy(tempy2);
        //qDebug() << "new pos" << tempChess1->getPosx() << "   " << tempChess1->getPosy();
        QPoint pos = GetChessPos(tempChess1->getPosx(), tempChess1->getPosy());
        tempChess1->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());

        tempChess1->setSelect(false);
        tempChess1->updatePic();
    }

    MovePoint.clear();
}
