#ifndef CARDLISTITEM_H
#define CARDLISTITEM_H

#include <QAbstractListModel>

class CardListModel: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CardListModel(QObject *parent = nullptr);
};

#endif // CARDLISTITEM_H
