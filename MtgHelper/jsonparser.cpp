#include "jsonparser.h"

QStringList JsonParser::GetCardList(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    QJsonArray jsonArray = jsonObject["data"].toArray();
    QStringList cardList;

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        cardList.append(name);
    }

    return cardList;
}

Card JsonParser::GetCard(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    Card card;

    return card;
}

void JsonParser::SetCardBasics(QByteArray* data, Card* card)
{

}

void JsonParser::SetCardArts(QByteArray* data, Card* card)
{

}

void JsonParser::SetCardLegalities(QByteArray* data, Card* card)
{

}

void JsonParser::SetCardURL(QByteArray* data, Card* card)
{

}

void JsonParser::SetCardID(QByteArray* data, Card* card)
{

}

//QList<Card>* JsonParser::GetCardList(QByteArray* data)
//{
//    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
//    QJsonArray jsonArray = jsonObject["data"].toArray();
//    QList<Card>* cardList = new QList<Card>();

//    foreach (const QJsonValue & value, jsonArray)
//    {
//        QJsonObject obj = value.toObject();
//        QString name = obj["name"].toString();
//        QString url  = obj["uri"].toString();

//        Card card(name, url);
//        cardList->append(card);
//    }

//    return cardList;
//}
