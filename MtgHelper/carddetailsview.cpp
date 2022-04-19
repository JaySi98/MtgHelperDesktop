#include "carddetailsview.h"

CardDetailsView::CardDetailsView(QObject* parent): QObject(parent)
{
    currentCardDetails = nullptr;
    currentCardImage = nullptr;
}

CardDetailsView::~CardDetailsView()
{
    if(currentCardDetails)
        delete currentCardDetails;
}

QWidget* CardDetailsView::GetCardDetailsView(Card card)
{
    if(currentCardDetails)
        delete currentCardDetails;

    // TODO
    currentCardDetails = new QWidget;

    return currentCardDetails;
}

QGraphicsScene* CardDetailsView::GetCardImage(QPixmap image)
{
    if(currentCardImage)
        delete currentCardImage;

    currentCardImage = new QGraphicsScene();
    QGraphicsPixmapItem item(image);
    currentCardImage->addItem(&item);

    return currentCardImage;
}
