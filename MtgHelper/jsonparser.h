#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QPixmap>
#include "card.h"

#define TEXT_CREATURE     "Creature"
#define TEXT_ARTIFACT     "Artifact"
#define TEXT_SORCERY      "Sorcery"
#define TEXT_INSTANT      "Instant"
#define TEXT_LAND         "Land"
#define TEXT_PLANESWALKER "Planeswalker"
#define TEXT_ENCHANTMENT  "Enchantment"
#define TEXT_LEGENDARY    "Legendary"


class JsonParser
{
public:
    static QString     GetNextPageURL(QByteArray* data);
    static bool        MoreThanSinglePage(QByteArray* data);
    static QStringList GetCardList(QByteArray* data);
    static Card        GetCard(QByteArray* data);
    static QPixmap     GetCardImage(QByteArray* data);

private:
    static bool IsCardDual(QJsonObject* jsonObject);
    static void SetCardBasics(QJsonObject* jsonObject, Card* card);
    static void SetCardArtInfo(QJsonObject* jsonObject, Card* card);
    static void SetCardURLS(QJsonObject* jsonObject, Card* card);
    static void SetCardID(QJsonObject* jsonObject, Card* card);

    static void SetSingleSideInfo(QJsonObject* jsonObject, Card* card);
    static void SetMultipleSideInfo(QJsonObject* jsonObject, Card* card);
    static SideInfo GetSideInfo(QJsonObject* jsonObject);
    static int GetCardType(QString line);
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
