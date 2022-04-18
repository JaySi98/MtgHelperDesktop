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

//    SetCardBasics(&jsonObject, &card);
//    SetCardArts(&jsonObject, &card);
//    SetCardURL(&jsonObject, &card);
//    SetCardID(&jsonObject, &card);

    return card;
}

QPixmap JsonParser::GetCardImage(QByteArray* data)
{
    QPixmap image;
    image.loadFromData(*data);
    return image;
}

void JsonParser::SetCardBasics(QJsonObject* jsonObject, SideInfo* card)
{
    card->name     = jsonObject->find("name")->toString();
    card->text     = jsonObject->find("oracle_text")->toString();
    card->typeLine = jsonObject->find("type_line")->toString();
    card->manaCost = jsonObject->find("mana_cost")->toString();
    card->cmc      = jsonObject->find("cmc")->toInt();
    card->setName  = jsonObject->find("set_name")->toString();
    card->rarity   = jsonObject->find("rarity")->toString();
    card->artist   = jsonObject->find("artist")->toString();

    QString power     = jsonObject->find("power")->toString();
    QString toughness = jsonObject->find("toughness")->toString();
    card->stats    = power + '/' + toughness;
}

void JsonParser::SetCardArts(QJsonObject* jsonObject, SideInfo* card)
{
    card->reserved = jsonObject->find("reserved")->toBool();
    card->foil     = jsonObject->find("foil")->toBool();
    card->nonfoil  = jsonObject->find("nonfoil")->toBool();
    card->fullArt  = jsonObject->find("full_art")->toBool();
}

void JsonParser::SetCardURL(QJsonObject* jsonObject, SideInfo* card)
{
    card->scryfallUrl = jsonObject->find("scryfall_uri")->toString();

    QJsonObject imageLinks = jsonObject->find("image_uris")->toObject();
    card->imageUrl = imageLinks.find("normal")->toString();
}

void JsonParser::SetCardID(QJsonObject* jsonObject, SideInfo* card)
{
    // TODO dokończyć
    card->mtgoID       = jsonObject->find("artist")->toInt();
    card->tcgPlayerID  = jsonObject->find("artist")->toInt();
    card->cardMarketID = jsonObject->find("artist")->toInt();
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
