#include "CardTransaction.h"

CardTransaction::CardTransaction(QObject *parent)
    : QObject{parent}
{}

void CardTransaction::save_card_collection(QSharedPointer<Card> card)
{
    //TODO
    // wyszukaj karty o takiej samej nazwie
    // jeżeli jest zwiększ licznik
    // inaczej dodaj nową
}

void CardTransaction::save_card_watchlist(QSharedPointer<Card> card)
{
    //TODO
    // wyszukaj kartę o takiej samej nazwie
    // jeżeli nie ma to dodaj
}
