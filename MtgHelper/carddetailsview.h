#ifndef CARDDETAILSVIEW_H
#define CARDDETAILSVIEW_H

#include <QObject>

class CardDetailsView: public QObject
{
    Q_OBJECT

public:
    explicit CardDetailsView(QObject* parent = nullptr);
};

#endif // CARDDETAILSVIEW_H
