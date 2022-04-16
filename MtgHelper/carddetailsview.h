#ifndef CARDDETAILSVIEW_H
#define CARDDETAILSVIEW_H

#include <QObject>
#include <QLayout>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsView>
#include "card.h"

class CardDetailsView: public QObject
{
    Q_OBJECT

public:
    explicit CardDetailsView(QObject* parent = nullptr);
    ~CardDetailsView();

    QWidget* GetCardDetailsView(Card card);
    void     SetCardImage(QPixmap image);

private:
    QWidget* currentView;

};

#endif // CARDDETAILSVIEW_H
