#ifndef CARDTRANSACTION_H
#define CARDTRANSACTION_H

#include <QObject>
#include <QtSql>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QSharedPointer>
#include <Api/Card.h>

class CardTransaction : public QObject
{
    Q_OBJECT
public:
    explicit CardTransaction(QObject *parent = nullptr);

    void save_card_collection(QSharedPointer<Card> card);
    void save_card_watchlist(QSharedPointer<Card> card);

signals:

private:

};

#endif // CARDTRANSACTION_H
