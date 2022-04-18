#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QAbstractListModel>

typedef enum
{
    CARD_TYPE_UNKNOWN  = 0x00,
    CARD_TYPE_CREATURE = 0x01,
    CARD_TYPE_INSTANT  = 0x02,
    CARD_TYPE_SORCERY  = 0x04,
    CARD_TYPE_LAND     = 0x08,
    CARD_TYPE_ARTIFACT = 0x10,
    CARD_TYPE_DUAL     = 0x20,
}cardType;

struct Card
{
    cardType type = CARD_TYPE_UNKNOWN;

    QString name;
    QString text;
    QString typeLine;
    QString manaCost;
    int cmc;
    QString stats;
    QString setName;
    QString rarity;
    QString artist;

    bool reserved;
    bool foil;
    bool nonfoil;
    bool fullArt;

    int mtgoID;
    int tcgPlayerID;
    int cardMarketID;

    QString scryfallUrl;
    QString imageUrl;

};

#endif // CARD_H
