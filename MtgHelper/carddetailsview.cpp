#include "carddetailsview.h"

CardDetailsView::CardDetailsView(QObject* parent): QObject(parent)
{ }

CardDetailsView::~CardDetailsView()
{ }

QWidget* CardDetailsView::GetCardDetailsView(Card card)
{
    QWidget* currentCardDetails = new QWidget;

    QLabel* cardImage = new QLabel(currentCardDetails);
    cardImage->setPixmap(card.details[SIDE_FACE].image);

    QVBoxLayout* mainLayout = new QVBoxLayout(currentCardDetails);
    mainLayout->addWidget(cardImage);
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

    return currentCardDetails;
}
