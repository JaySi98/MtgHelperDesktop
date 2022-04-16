#include "carddetailsview.h"

CardDetailsView::CardDetailsView(QObject* parent): QObject(parent)
{
    currentView = nullptr;
}

CardDetailsView::~CardDetailsView()
{
    if(currentView)
        delete currentView;
}

QWidget* CardDetailsView::GetCardDetailsView(Card card)
{
    if(currentView)
        delete currentView;

    // TODO
    currentView = new QWidget;

    return currentView;
}

void CardDetailsView::SetCardImage(QPixmap image)
{
    // TODO
}
