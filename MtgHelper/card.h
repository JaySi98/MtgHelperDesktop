#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QAbstractListModel>

enum gameTypes
{
    GAME_TYPE_STANDARD          = 0,
    GAME_TYPE_FUTURE            = 1,
    GAME_TYPE_HISTORIC          = 2,
    GAME_TYPE_GLADIATOR         = 3,
    GAME_TYPE_PIONEER           = 4,
    GAME_TYPE_MODERN            = 5,
    GAME_TYPE_LEGACY            = 6,
    GAME_TYPE_PAUPER            = 7,
    GAME_TYPE_VINTAGE           = 8,
    GAME_TYPE_PENNY             = 9,
    GAME_TYPE_COMMANDER         = 10,
    GAME_TYPE_BRAWL             = 11,
    GAME_TYPE_HISTORIC_BRAWL    = 12,
    GAME_TYPE_ALCHEMY           = 13,
    GAME_TYPE_PAUPER_COMMANDER  = 14,
    GAME_TYPE_DUEL              = 15,
    GAME_TYPE_OLDSCHOOL         = 16,
    GAME_TYPE_PREMODERN         = 17,
};

struct Card
{
    QString name;
    QString text;
    QString type;
    QString manaCost;
    QString cmc;
    QString stats;
    QString setName;
    QString rarity;
    QString artist;

    bool reserved;
    bool foil;
    bool nonfoil;
    bool fullArt;

    QStringList legalities;

    int mtgoID;
    int tcgPlayerID;
    int cardMarketID;

    QString scryfallUrl;
    QString imageUrl;

};

#endif // CARD_H
