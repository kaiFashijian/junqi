#ifndef IMG_H
#define IMG_H

#include "public.h"

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>


class Img : public QObject
{
    Q_OBJECT
public:
    explicit Img(QObject *parent = nullptr);
    void upload(QString img_path); // 上传图片到图床
    void download(QString img_url);  // 根据url下载图片

signals:

private slots:
    void uploadHandler(QNetworkReply *reply); // 保存图片的url到本地用户的属性中
};

#endif // IMG_H
