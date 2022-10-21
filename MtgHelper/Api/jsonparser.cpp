#include "jsonparser.h"

 QString JsonParser::GetNextPageURL(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    QString url = jsonObject["next_page"].toString();

    return url;
}

bool JsonParser::MoreThanSinglePage(QByteArray *data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    QJsonArray jsonArray = jsonObject["data"].toArray();

    int cardsTotal = jsonObject["total_cards"].toInt();
    int cardsOnJson = 0;

    foreach (const QJsonValue & value, jsonArray)
    {
        ++cardsOnJson;
    }

    return (cardsTotal > cardsOnJson);
}

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

QPixmap JsonParser::GetCardImage(QByteArray* data)
{
    QPixmap image;
    image.loadFromData(*data);
    return image;
}

Card* JsonParser::GetCard(QByteArray* data)
{
    QJsonObject jsonObject = QJsonDocument::fromJson(*data).object();
    Card* card = new Card();

    SetCardBasics(&jsonObject, card);
    card->isDual = IsCardDual(&jsonObject);

    if(card->isDual)
        SetMultipleSideInfo(&jsonObject, card);
    else
        SetSingleSideInfo(&jsonObject, card);

    return card;
}

void JsonParser::SetCardBasics(QJsonObject* jsonObject, Card* card)
{
    card->cmc      = jsonObject->find("cmc")->toInt();
    card->setName  = jsonObject->find("set_name")->toString();
    card->rarity   = jsonObject->find("rarity")->toString();

    card->mtgoID       = jsonObject->find("mtgo_id")->toInt();
    card->tcgPlayerID  = jsonObject->find("tcgplayer_id")->toInt();
    card->cardMarketID = jsonObject->find("cardmarket_id")->toInt();

    card->reserved = jsonObject->find("reserved")->toBool();
    card->foil     = jsonObject->find("foil")->toBool();
    card->nonfoil  = jsonObject->find("nonfoil")->toBool();
    card->fullArt  = jsonObject->find("full_art")->toBool();
}

void JsonParser::SetSingleSideInfo(QJsonObject* jsonObject, Card* card)
{
    SideInfo sideInfo = GetSideInfo(jsonObject);
    card->details.append(sideInfo);
}

void JsonParser::SetMultipleSideInfo(QJsonObject* jsonObject, Card* card)
{
    QJsonArray jsonArray = jsonObject->find("card_faces")->toArray();

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        SideInfo sideInfo = GetSideInfo(&obj);
        card->details.append(sideInfo);
    }
}

SideInfo JsonParser::GetSideInfo(QJsonObject* jsonObject)
{
    SideInfo sideInfo;

    sideInfo.typeLine = jsonObject->find("type_line")->toString();
    sideInfo.cardType = GetCardType(sideInfo.typeLine);

    sideInfo.name     = jsonObject->find("name")->toString();
    sideInfo.text     = jsonObject->find("oracle_text")->toString();
    sideInfo.manaCost = jsonObject->find("mana_cost")->toString();
    sideInfo.artist   = jsonObject->find("artist")->toString();

    if(sideInfo.cardType & CARD_TYPE_CREATURE)
    {
        QString power     = jsonObject->find("power")->toString();
        QString toughness = jsonObject->find("toughness")->toString();
        sideInfo.stats    = power + '/' + toughness;
    }
    else if(sideInfo.cardType & CARD_TYPE_PLANESWALKER)
    {
        sideInfo.stats = jsonObject->find("loyalty")->toString();
    }

    QJsonObject imageLinks = jsonObject->find("image_uris")->toObject();
    sideInfo.imageUrl = imageLinks.find("normal")->toString();

    return sideInfo;
}

bool JsonParser::IsCardDual(QJsonObject* jsonObject)
{
    return jsonObject->contains("card_faces");
}

int JsonParser::GetCardType(QString line)
{
    int type = CARD_TYPE_UNKNOWN;

    if(line.contains(TEXT_CREATURE))
        type |= CARD_TYPE_CREATURE;
    if(line.contains(TEXT_ARTIFACT))
        type |= CARD_TYPE_ARTIFACT;
    if(line.contains(TEXT_INSTANT))
        type |= CARD_TYPE_INSTANT;
    if(line.contains(TEXT_SORCERY))
        type |= CARD_TYPE_SORCERY;
    if(line.contains(TEXT_LAND))
        type |= CARD_TYPE_LAND;
    if(line.contains(TEXT_ENCHANTMENT))
        type |= CARD_TYPE_ENCHANTMENT;
    if(line.contains(TEXT_PLANESWALKER))
        type |= CARD_TYPE_PLANESWALKER;
    if(line.contains(TEXT_LEGENDARY))
        type |= CARD_TYPE_LEGENDARY;

    return type;
}
