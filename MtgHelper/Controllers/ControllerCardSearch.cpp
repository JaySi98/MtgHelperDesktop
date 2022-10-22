#include "ControllerCardSearch.h"

ControllerCardSearch::ControllerCardSearch(QObject *parent)
    : QObject{parent}
    , api_connector(QSharedPointer<APIConnector>(new APIConnector()))
    , card_list(QList<QSharedPointer<Card>>())
    , current_card(nullptr)
{
   connect(api_connector.get(), &APIConnector::CardListRead,    this, &ControllerCardSearch::card_list_fetched);
   connect(api_connector.get(), &APIConnector::CardDetailsRead, this, &ControllerCardSearch::set_card_details);
   connect(api_connector.get(), &APIConnector::CardImageRead,   this, &ControllerCardSearch::set_card_image);
}


void ControllerCardSearch::get_card_list(QString query)
{
    card_list.clear();
    current_card = nullptr;
    api_connector->SearchCardList(query);
}

void ControllerCardSearch::get_card_details(QString card_name)
{
    if(card_already_displayed(card_name))
    {
        current_card = get_card(card_name);
        emit card_details_fetched(current_card.get());
    }
    else
    {
        api_connector->SearchCardDetails(card_name);
    }
}

void ControllerCardSearch::set_card_details(Card* card)
{
    QSharedPointer<Card> pCard = QSharedPointer<Card>(card);
    card_list.append(pCard);
    current_card = pCard;

    api_connector->SearchCardImage(current_card.get()->details[SIDE_FACE].imageUrl);
}

void ControllerCardSearch::set_card_image(QPixmap image)
{
    current_card.get()->details[SIDE_FACE].image = image;
    emit card_details_fetched(current_card.get());
}

bool ControllerCardSearch::card_already_displayed(QString card_name)
{
    foreach(QSharedPointer<Card> card, card_list)
    {
        if(card.get()->details[0].name.compare(card_name) == 0)
            return true;
    }

    return false;
}

QSharedPointer<Card> ControllerCardSearch::get_card(QString card_name)
{
    foreach(QSharedPointer<Card> card, card_list)
    {
        if(card.get()->details[0].name.compare(card_name) == 0)
            return card;
    }

    throw std::out_of_range("no card in list");
}

