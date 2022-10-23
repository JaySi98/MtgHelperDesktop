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

signals:
    void card_list_fetched(QStringList card_list);
    void card_details_fetched(Card* card);

public slots:
    void get_card_list(QString query);
    void get_card_details(QString card_name);
    void set_card_details(Card* card);
    void set_card_image(QPixmap image);

private:
    QSharedPointer<APIConnector> api_connector;
    QSharedPointer<Card>         current_card;
    QList<QSharedPointer<Card>>  card_list;     // cards already displayed

    bool card_already_displayed(QString card_name);
    QSharedPointer<Card> get_card(QString card_name);
};

#endif // CONTROLLERCARDSEARCH_H
