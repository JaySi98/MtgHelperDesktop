#ifndef CONTROLLERCARDSEARCH_H
#define CONTROLLERCARDSEARCH_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QStringList>
#include <Api/apiconnector.h>
#include <Api/Card.h>

class ControllerCardSearch : public QObject
{
    Q_OBJECT
public:
    explicit ControllerCardSearch(QObject *parent = nullptr);
    QPixmap get_card_flip_image(int side);

signals:
    void card_list_fetched(QStringList card_list);
    void card_details_fetched(Card* card);
    void card_to_collection(Card* card);
    void card_to_watchlist(Card* card);

public slots:
    void get_card_list(QString query);
    void get_card_details(QString card_name);
    void set_card_details(Card* card);
    void set_card_image(QPixmap image);
    void set_card_back_image(QPixmap image);
    void add_card_to_collection();
    void add_card_to_watchlist();

private:
    QSharedPointer<APIConnector> api_connector;
    QSharedPointer<Card>         current_card;
    QList<QSharedPointer<Card>>  card_list;     // cards already displayed

    bool card_already_displayed(QString card_name);
    QSharedPointer<Card> get_card(QString card_name);
};

#endif // CONTROLLERCARDSEARCH_H
