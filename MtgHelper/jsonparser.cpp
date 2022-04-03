#include "jsonparser.h"

QList<Card>* JsonParser::GetCardList(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    QJsonArray jsonArray = jsonObject["data"].toArray();
    QList<Card>* cardList = new QList<Card>();

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString url  = obj["uri"].toString();

        Card card(name, url);
        cardList->append(card);
    }

    return cardList;
}

Card JsonParser::GetCard(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    Card card;

    return card;
}
