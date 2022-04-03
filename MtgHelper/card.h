#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{
public:
    Card();
    Card(QString name, QString url);

    QString name;
    QString urlScryfall;
    QString text;
    QString cmc;
};

#endif // CARD_H
