#ifndef PUBLIC_H
#define PUBLIC_H
#include<QTcpSocket>
#include<QDataStream>
#include<QVector>
#include<QPoint>




//棋盘的变量

// 地图大小
#define GAME_MAP_HEIGHT 923
#define GAME_MAP_WIDTH  650

// 格子大小
#define GAME_CELL_HEIGHT    44
#define GAME_CELL_WIDTH     86

// 格子间隔
#define GAME_OFF_HEIGHT     19
#define GAME_OFF_WIDTH      45

// 上棋盘偏移
#define GAME_UP_HEIGHT     19
#define GAME_UP_WIDTH      20

// 下棋盘偏移
#define GAME_DOWN_HEIGHT     537
#define GAME_DOWN_WIDTH      20

// 棋格状态
enum CHESS_TYPE{
    CHESS_UNKONWN = 0,
    CHESS_FALG,         // 军旗   1
    CHESS_MINE,         // 地雷   3
    CHESS_BOMB,         // 炸弹   2
    CHESS_Commande,     // 司令   1
    CHESS_General,      // 军长   1
    CHESS_Maj_general,  // 师长   2
    CHESS_Brigadier,    // 旅长   2
    CHESS_Colonel,      // 团长   2
    CHESS_Major,        // 营长   2
    CHESS_Captain,      // 连长   3
    CHESS_Lieutenant,   // 排长   3
    CHESS_Engineer      // 工兵   3
};

// 阵营
enum CAMP_TYPE{
    RED,
    BLUE
};

//棋盘函数

// 获取各个棋子的数量
int GetChessTypeNum(CHESS_TYPE type);

// 获取各种类型棋子图片
QString GetChessPic(CHESS_TYPE type, CAMP_TYPE camp);

QString GetChessCampIntoString(CAMP_TYPE camp);
QString GetChessTypeIntoString(CHESS_TYPE type);


//游戏内变量

//用于确定自己的刚开始时翻出的红蓝方棋子的多少
extern int red_num;
extern int blue_num;

extern QString myColor;//我的阵营

extern bool myTurn;//我的轮次
extern int overTime;//超时次数
extern int seed;//随机种子

extern QPoint TurnPoint;
extern QVector<QPoint> MovePoint;
//存储点击棋子的坐标，方便走棋子判断
extern QVector<QPoint> movePoint;
//存储棋子翻转的坐标，方便棋子翻转
extern QVector<QPoint> turnPoint;
//存储发送过来的棋子坐标


//表情文字收集
extern QStringList emojiStr;


extern QMap<QString,int> mapForQiDisplay;



#endif // PUBLIC_H
