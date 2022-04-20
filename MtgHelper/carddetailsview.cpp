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
    buildCardDetails(card);

    return currentCardDetails;
}

QGraphicsScene* CardDetailsView::GetCardImage(QPixmap image)
{
    if(currentCardImage)
        delete currentCardImage;

    currentCardImage = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(image);
    currentCardImage->addItem(item);

    return currentCardImage;
}

void CardDetailsView::buildCardDetails(Card card)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(currentCardDetails);
    mainLayout->addWidget(new QLabel(card.details[SIDE_FACE].name, currentCardDetails));
    mainLayout->addWidget(new QLabel(card.details[SIDE_FACE].typeLine, currentCardDetails));
    mainLayout->addWidget(new QLabel(card.details[SIDE_FACE].manaCost, currentCardDetails));

    QPlainTextEdit* textEdit = new QPlainTextEdit(currentCardDetails);
    textEdit->appendPlainText(card.details[SIDE_FACE].text);
    textEdit->setReadOnly(true);
    textEdit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    mainLayout->addWidget(textEdit);

    if(card.details[SIDE_FACE].cardType & CARD_TYPE_CREATURE || card.details[SIDE_FACE].cardType & CARD_TYPE_PLANESWALKER )
        mainLayout->addWidget(new QLabel(card.details[SIDE_FACE].stats, currentCardDetails));
    mainLayout->addWidget(new QLabel(card.rarity, currentCardDetails));
    mainLayout->addWidget(new QLabel(card.setName, currentCardDetails));
}
