#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QAbstractListModel>

enum cardSide
{
    SIDE_FACE = 0,
    SIDE_BACK = 1
};

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

struct SideInfo
{
    QString name;
    QString text;
    QString typeLine;
    QString manaCost;
    QString stats;
    QString imageUrl;
    QString artist;
};


struct Card
{
    cardType type = CARD_TYPE_UNKNOWN;
    QList<SideInfo> details;

    QString scryfallUrl;
    QString setName;
    QString rarity;

    bool reserved;
    bool foil;
    bool nonfoil;
    bool fullArt;

    int cmc;
    int mtgoID;
    int tcgPlayerID;
    int cardMarketID;
};

#endif // CARD_H
