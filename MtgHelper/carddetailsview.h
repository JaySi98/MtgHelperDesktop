#ifndef CARDDETAILSVIEW_H
#define CARDDETAILSVIEW_H

#include <QObject>
#include <QLayout>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPlainTextEdit>
#include "card.h"

class CardDetailsView: public QObject
{
    Q_OBJECT

public:
    explicit CardDetailsView(QObject* parent = nullptr);
    ~CardDetailsView();

    QWidget* GetCardDetailsView(Card card);
    QGraphicsScene* GetCardImage(QPixmap image);

private:
    QWidget* currentCardDetails;
    QGraphicsScene* currentCardImage;

    void buildCardDetails(Card card);
};

#endif // CARDDETAILSVIEW_H
