#include "CardTransaction.h"

CardTransaction::CardTransaction(QObject *parent)
    : QObject{parent}
{}

void CardTransaction::save_card_collection(QSharedPointer<Card> card)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT * FROM mtg_helper.cards WHERE name = :name;");
    query.bindValue(":name", card->get_name());

    query.exec();
    if (query.next()) 
    {
        int current_amount = query.value(2).toInt();

        query.prepare("UPDATE mtg_helper.cards SET amount = :amount WHERE name = :name");
        query.bindValue(":amount",  ++current_amount);
        query.bindValue(":name",    card->get_name());
    }
    else
    {
        query.prepare("INSERT INTO mtg_helper.cards(id, name, amount, observed, owned)"
                      "VALUES (:id, :name, :amount, :observed, :owned);");
        query.bindValue(":id",      0);
        query.bindValue(":name",    card->get_name());
        query.bindValue(":amount",  0);
        query.bindValue(":observed",false);
        query.bindValue(":owned",   true);
    }

    if(!query.exec())
    {
        qInfo() << QSqlDatabase::database().lastError().text();
        qInfo() << query.lastError().text();
    }

    QSqlDatabase::database().commit();
}

void CardTransaction::save_card_watchlist(QSharedPointer<Card> card)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT * FROM mtg_helper.cards WHERE name = :name");
    query.bindValue(":name", card->get_name());

    query.exec();
    if(query.next())
    {
        // card owned but not observed
        if(!query.value(3).toBool())
        {
            query.prepare("UPDATE mtg_helper.cards SET observed = :observed WHERE name = :name");
            query.bindValue(":observed",  true);
            query.bindValue(":name",      card->get_name());
        }
    }
    else
    {
        // new card to database
        query.prepare("INSERT INTO mtg_helper.cards(id, name, amount, observed, owned)"
                      "VALUES (:id, :name, :amount, :observed, :owned);");
        query.bindValue(":id",      0);
        query.bindValue(":name",    card->get_name());
        query.bindValue(":amount",  0);
        query.bindValue(":observed",true);
        query.bindValue(":owned",   false);
    }

    if(!query.exec())
    {
        qInfo() << QSqlDatabase::database().lastError().text();
        qInfo() << query.lastError().text();
    }

    QSqlDatabase::database().commit();
}
