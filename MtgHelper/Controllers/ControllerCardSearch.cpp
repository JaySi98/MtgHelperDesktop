#include "ControllerCardSearch.h"

ControllerCardSearch::ControllerCardSearch(QObject *parent)
    : QObject{parent}
    , api_connector(QSharedPointer<APIConnector>(new APIConnector()))
    , card_list(QList<QSharedPointer<Card>>())
    , current_card(nullptr)
{
   connect(api_connector.get(), &APIConnector::CardListRead,    this, &ControllerCardSearch::card_list_fetched);
   connect(api_connector.get(), &APIConnector::CardDetailsRead, this, &ControllerCardSearch::set_card_details);

   connect(api_connector.get(), &APIConnector::CardImageFrontRead,  this, &ControllerCardSearch::set_card_image);
   connect(api_connector.get(), &APIConnector::CardImageBackRead,   this, &ControllerCardSearch::set_card_back_image);
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

    api_connector->SearchCardFrontImage(current_card.get()->get_image_url(SIDE_FACE));
}

void ControllerCardSearch::set_card_image(QPixmap image)
{
    current_card.get()->set_image(SIDE_FACE, image);

    if(current_card.get()->isDual)
    {
        api_connector->SearchCardBackImage(current_card.get()->get_image_url(SIDE_BACK));
    }
    else
    {
        emit card_details_fetched(current_card.get());
    }
}

void ControllerCardSearch::set_card_back_image(QPixmap image)
{
    current_card.get()->set_image(SIDE_BACK, image);
    emit card_details_fetched(current_card.get());
}

void ControllerCardSearch::add_card_to_collection()
{
    // TODO
}

void ControllerCardSearch::add_card_to_watchlist()
{
    // TODO
}

QPixmap ControllerCardSearch::get_card_flip_image(int side)
{
    return current_card.get()->get_image(side);
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

