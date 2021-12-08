#include "img.h"

Img::Img(QObject *parent) : QObject(parent){}

void Img::upload(QString img_path){
    //网络载体
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    //网络载体的响应接收信号，与响应接收槽绑定
    connect(manager, &QNetworkAccessManager::finished, this, &Img::uploadHandler);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    //如果上传的是jpg图片，就修改为image/jpg
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"smfile\"; filename=\"image.png\""));
    //这里的smfile是参数名，不可以修改，因为SM.MS的API接口要求参数名必须为smfile
    //下面这行代码的作用是打开选择窗口，选择一个图片并返回路径
    // QString strFilePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择上传图片"), "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm *.jpeg);;All files (*.*)"));
    // QFile *file = new QFile(strFilePath);

    QFile *file = new QFile(img_path);
    if(!file->open(QIODevice::ReadOnly)){
        qDebug()<<"=================================";
    } else {
        imagePart.setBodyDevice(file);
        multiPart->append(imagePart);
    }

    QNetworkRequest request;
    request.setUrl(QUrl("https://sm.ms/api/v2/upload")); // v1 已经弃用
    manager->post(request,multiPart);
}

void Img::uploadHandler(QNetworkReply *reply){
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "statusCode:" << statusCode;

    if(reply->error() == QNetworkReply::NoError) {
        //官方文档显示返回的reply是json格式，所以我们采用json格式读取
        qDebug() << "!!!!!!!!!!";
        QByteArray allData = reply->readAll();
        QJsonParseError *json_error = new QJsonParseError();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, json_error));
        if (json_error->error != QJsonParseError::NoError) {
            qDebug() << "json error!" << json_error->errorString();
            return;
        }
        QJsonObject obj = jsonDoc.object();


        //我们只需要上传后的url，所以值提取了url，如果你需要其他内容，请提取方法类似
        if (obj.contains("data")) {
            qDebug() << "heereerer";
            QJsonObject subObj = obj.value("data").toObject();
            local_user.icon_url = subObj["url"].toString(); // 把返回的url保存到本地用户的属性中
        }
    } else {
        qDebug() << "=========";
    }

    reply->deleteLater();
}

void Img::download(QString img_url){
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl(img_url));
    connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply){
        QString url = img_url;
        QString filePath = "../";

        const QString fileName = filePath + url.right(url.size() - url.lastIndexOf("/"));
        qDebug() << fileName;

        QFile file;

        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);
        if (!file.isOpen()) {
            qDebug() << "file is not open";
            return;
        }

        if (!file.isWritable()) {
            qDebug() << "file write disable";
            return;
        }

        file.write(reply->readAll());
        file.close();
    });
    manager->get(request);
}
