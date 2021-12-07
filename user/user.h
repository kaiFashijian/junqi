#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>

class User {
public:
    QString uid;
    QString name;
    int scores;
    QString icon_url;
    QStringList friends_list;
};

#endif // USER_H
