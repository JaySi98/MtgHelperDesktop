#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QAbstractListModel>
#include <QPixmap>

enum cardSide
{
    SIDE_FACE = 0,
    SIDE_BACK = 1
};

enum cardType
{
    CARD_TYPE_UNKNOWN  = 0x00,
    CARD_TYPE_CREATURE = 0x01,
    CARD_TYPE_INSTANT  = 0x02,
    CARD_TYPE_SORCERY  = 0x04,
    CARD_TYPE_LAND     = 0x08,
    CARD_TYPE_ARTIFACT = 0x10,
    CARD_TYPE_ENCHANTMENT  = 0x20,
    CARD_TYPE_PLANESWALKER = 0x40,
    CARD_TYPE_LEGENDARY    = 0x80,
};

struct SideInfo
{
    int cardType = CARD_TYPE_UNKNOWN;

    QString name;
    QString text;
    QString typeLine;
    QString manaCost;
    QString stats;
    QString imageUrl;
    QString artist;

    QPixmap image;
};


struct Card
{
    QList<SideInfo> details;

    QString scryfallUrl;
    QString setName;
    QString rarity;

    bool isDual;
    bool reserved;
    bool foil;
    bool nonfoil;
    bool fullArt;

    int cmc;
    int mtgoID;
    int tcgPlayerID;
    int cardMarketID;

    QString get_name();
    void    set_image(int side, QPixmap image);
    QPixmap get_image(int side);
    QString get_image_url(int side);
};

#endif // CARD_H
