#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include "card.h"

#define MAX_CARD_COUNT 100

class JsonParser
{
public:
    static QList<Card>* GetCardList(QByteArray* data);
    static Card GetCard(QByteArray* data);
};

#endif // JSONPARSER_H


//CONVERT THE DATA FROM A JSON DOC TO A JSON OBJECT
//        QJsonObject userJsonInfo = QJsonDocument::fromJson(*dataBuffer).object();
//        QJsonObject card = userJsonInfo.find("card")->toObject();

//SET PICTURE
//        auto picLink = userJsonInfo.value("avatar_url").toString();
//        QNetworkRequest link{QUrl(picLink)};
//        reply = netManager->get(link);
//        connect(reply,&QNetworkReply::finished,this,&MainWindow::setUserImage);
