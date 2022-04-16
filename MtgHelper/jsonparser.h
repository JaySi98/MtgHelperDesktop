#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QPixmap>

#include "card.h"

#define MAX_CARD_COUNT 100

class JsonParser
{
public:
//    static QList<Card>* GetCardList(QByteArray* data);
    static QStringList GetCardList(QByteArray* data);
    static Card GetCard(QByteArray* data);
    static QPixmap GetCardImage(QByteArray* data);

private:
    static void SetCardBasics(QJsonObject* jsonObject, Card* card);
    static void SetCardArts(QJsonObject* jsonObject, Card* card);
    static void SetCardURL(QJsonObject* jsonObject, Card* card);
    static void SetCardID(QJsonObject* jsonObject, Card* card);

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
