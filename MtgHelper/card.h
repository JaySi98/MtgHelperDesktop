#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QAbstractListModel>

struct Card
{
    QString name;
    QString text;
    QString type;
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
