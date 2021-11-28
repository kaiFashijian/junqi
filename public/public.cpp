#include "public.h"
using namespace std;

//游戏内变量初始化
int red_num = 0;
int blue_num = 0;
QString myColor;
bool myTurn = true;
int overTime = 0;

//产生棋盘的种子 打算丢给服务器产生
int seed = 100;

QVector<QPoint> movePoint;
QVector<QPoint> turnPoint;
//QPoint SendTurnPoint;
int Turnx = 0;
int Turny = 0;

QVector<QPoint> MovePoint;
QPoint TurnPoint;


int GetChessTypeNum(CHESS_TYPE type)
{
    switch (type) {
    case CHESS_FALG:
    case CHESS_Commande:
    case CHESS_General:
        return 1;
    case CHESS_BOMB:
    case CHESS_Maj_general:  // 师长   2
    case CHESS_Brigadier:    // 旅长   2
    case CHESS_Colonel:    // 团长   2
    case CHESS_Major:        // 营长   2
        return  2;
    case CHESS_MINE:
    case CHESS_Captain:      // 连长   3
    case CHESS_Lieutenant:   // 排长   3
    case CHESS_Engineer:      // 工兵   3
        return 3;
    default:
        return 0;
    }
}

QString GetChessPic(CHESS_TYPE type, CAMP_TYPE camp)
{
    QString qsUrl = ":/images/";
    if(type == CHESS_UNKONWN)
        return qsUrl += "chess.png";

    if(camp == RED)
        qsUrl += "red_";
    else
        qsUrl += "blue_";

    switch (type) {
    case CHESS_FALG:
        qsUrl += "flag";
        break;
    case CHESS_Commande:
        qsUrl += "Commande";
        break;
    case CHESS_General:
        qsUrl += "General";
        break;
    case CHESS_BOMB:
        qsUrl += "bomb";
        break;
    case CHESS_Maj_general:
        qsUrl += "Maj_general";
        break;
    case CHESS_Brigadier:
        qsUrl += "Brigadier";
        break;
    case CHESS_Colonel:
        qsUrl += "Colonel";
        break;
    case CHESS_Major:
        qsUrl += "Major";
        break;
    case CHESS_MINE:
        qsUrl += "mine";
        break;
    case CHESS_Captain:
        qsUrl += "Captain";
        break;
    case CHESS_Lieutenant:
        qsUrl += "Lieutenant";
        break;
    case CHESS_Engineer:
        qsUrl += "engineer";
        break;
    default:
        return "";
    }
    qsUrl += ".png";
    return qsUrl;
}


QStringList emojiStr = {"😄","😆","😊","😃","😏","😍","😘","😚","😳",
                        "😌","😆","😁","😉","😜","😝","😀","😗","😙","😛","😴",
                        "😟","😦","😧","😮","😬","😕","😯","😑","😒","😅","😓",
                        "😥","😩","😔","😞","😖","😨","😰","😣","😢","😭","😂",
                        "😲","😱","😫","😠","😡","😤","😪","😋","😷","😎","😵",
                        "👿","😈","😐","😶","😇","👽","💛","💙","💜","💚","💔",
                        "💆","💇","💅","👦","👧","👩","💙","💜","💚","💔","💆",
                        "💇","💅","👦","👧","👩"};
//        "👸😺😸😻😽😼🙀😿😹😾👹👺🙈🙉🙊💂💀🐾👄💋"
//        "💧👂👀👃👅💌👤👥💬💭"
//        "🎍💝🎎🎒🎓🎏🎆🎇🎐🎑📂📌📎📏📐📕📗"
//        "🎃👻🎅🎄🎁🔔🔕🎋🎉🎊📘📙📓📔📒📚🔖📛🔬🔭"
//        "🎈🔮💿📀💾📷📹🎥💻📺📰🏈🏀⚽️⚾️🎾🎱🏉🎳"
//        "📱☎️📞📟📠💽📼🔉🔈🔇⛳️🚵🚴🏇🏂🏊🏄🎿"
//        "📢📣⏳⏰📻📡➿🔍💎💍🏆🎼🎹🎻👾🎮🃏🎴"
//        "🔎🔓🔏🔐🔑💡🔦🔆🔅🎲🎯🀄️🎬📝📝📖🎨🎤🎧"
//        "🔌🔋📲📫📮🛀🛁🚿🚽🎺🎷🎸👞👡👠💄👢👕👔"
//        "🔧🔩🔨💺💰💴💵💷💶💳👚👗🎽👖👘👙🎀🎩👑👒"
//        "💸📧📥📤📨📯📪📬📭👞🌂💼👜👝👛👓🎣🍵"
//        "📦🚪🚬💣🔫🔪💊💉📄📃📑📊📈📉📜📋📆📅📇📁"
//        "🍶🍼🍺🍻🍸🍹🍷🍴🍕🍔🍟🍗🍖🍝🍛🍤🍱🍣🍥🍙🍘"
//        "🍚🍜🍲🍢🍡🥚🍞🍩🍮🍦🍨🍧🎂🍰🍪🍫🍬🍭🍯🍎"
//        "🍏🍊🍋🍒🍇🍉🍓🍑🍈🍌🍐🍍🍠🍆🍅🌽";

