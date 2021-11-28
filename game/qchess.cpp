#include "qchess.h"

QChess::QChess(CAMP_TYPE camp, CHESS_TYPE type, int forx, int fory, QWidget *parent) :
    QPushButton(parent),
    m_bShown(false),
    m_camp(camp),
    m_type(type),
    m_bSelect(false),
    posx(forx),
    posy(fory)
{
    updatePic();
}


void QChess::mousePressEvent(QMouseEvent *event)
{

    if(!myTurn)  return ;

    else
    {
        //myTurn = false;

        //翻转棋子 不能走棋时的选项
        if(!m_bShown)
        {
            if(movePoint.size() != 0)
                return ;

            m_bShown = true;
            qDebug() << "qchess鼠标点击翻转" << this->m_camp << "级别" << this->m_type << this->posx << this->posy;
            updatePic();

            movePoint.push_back(QPoint(this->posx, this->posy));

            //通知上层发送翻转信息
            emit QiTurn();
            return ;
        }

        //再次点击棋子想要跳转
        else
        {
            m_bSelect = !m_bSelect;
            if(!m_bSelect)
            {
                movePoint.clear();
                updatePic();
            }
            else
            {
                movePoint.push_back(QPoint(this->posx,this->posy));
                if(movePoint.size() == 2)
                {
                    //发送上层做走棋判断
                    emit moveButton();
                }

                updatePic();
            }
        }

    }
}

int QChess::getPosx()
{
   return this->posx;
}

int QChess::getPosy()
{
    return this->posy;
}

CAMP_TYPE QChess::getCamp()
{
    return this->m_camp;
}

CHESS_TYPE QChess::getType()
{
    return this->m_type;
}

void QChess::setPosx(int newX)
{
    this->posx = newX;
}

void QChess::setPosy(int newY)
{
    this->posy = newY;
}

void QChess::setSelect(bool flag)
{
    this->m_bSelect = flag;
}
void QChess::setShow(bool flag)
{
    this->m_bShown = true;
}
void QChess::updatePic()
{
    QString qsUrl = "border-image:url(";
    if(m_bShown == false){
        qsUrl += GetChessPic(CHESS_UNKONWN, m_camp);
    }else{
        qsUrl += GetChessPic(m_type, m_camp);
    }
    qsUrl += ");";
    if(m_bSelect)
       qsUrl += "border-width:5px;border-radius:10px;border-color: rgb(34, 255, 145);";


    setStyleSheet(qsUrl);
}


